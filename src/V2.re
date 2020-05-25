/**
   Type definitions for AWS Lambda v1 Payload
   http://docs.aws.amazon.com/lambda
   https://docs.aws.amazon.com/apigateway/latest/developerguide/http-api-develop-integrations-lambda.html
 */
module Response = {
  type t('a);

  [@bs.obj]
  external make:
    (
      ~cookies: array(string)=?,
      ~isBase64Encoded: bool=?,
      ~statusCode: int=?,
      ~headers: Js.Dict.t(string)=?,
      ~body: 'a=?,
      unit
    ) =>
    t('a);
};

module Context = Common.Context;

module Authorizer = {
  type jwt = {
    claims: option(Js.Dict.t(string)),
    scopes: option(array(string)),
  };

  type t = {jwt};
};

module Http = {
  type t = {
    method: string,
    path: string,
    protocol: string,
    sourceIp: string,
    userAgent: string,
  };
};

module RequestContext = {
  type t = {
    accountId: string,
    apiId: string,
    authorizer: option(Authorizer.t),
    domainName: string,
    domainPrefix: string,
    http: Http.t,
    requestId: string,
    routeKey: string,
    stage: string,
    time: string,
    timeEpoch: float,
  };
};

module Event = {
  type t = {
    version: string,
    routeKey: string,
    rawPath: string,
    rawQueryString: string,
    cookies: array(string),
    headers: Js.Dict.t(string),
    queryStringParameters: option(Js.Dict.t(string)),
    requestContext: RequestContext.t,
    body: Js.Json.t,
    pathParameters: option(Js.Dict.t(string)),
    isBase64Encoded: bool,
    stageVariables: option(Js.Dict.t(string)),
  };
};

type handler('a) = (Event.t, Context.t) => Js.Promise.t(Response.t('a));