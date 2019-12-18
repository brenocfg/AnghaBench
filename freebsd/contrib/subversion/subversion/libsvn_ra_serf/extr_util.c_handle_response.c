#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_ra_serf__server_error_t ;
struct TYPE_23__ {scalar_t__ version; int code; int /*<<< orphan*/  reason; } ;
struct TYPE_21__ {int /*<<< orphan*/  response_baton; TYPE_4__* (* response_handler ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/ * server_error; void* discard_body; void* reading_body; TYPE_5__ sline; int /*<<< orphan*/  handler_pool; TYPE_2__* conn; TYPE_1__* session; int /*<<< orphan*/  location; int /*<<< orphan*/  method; int /*<<< orphan*/  path; int /*<<< orphan*/  response_error_baton; int /*<<< orphan*/  (* response_error ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;void* scheduled; } ;
typedef  TYPE_3__ svn_ra_serf__handler_t ;
struct TYPE_22__ {scalar_t__ apr_err; } ;
typedef  TYPE_4__ svn_error_t ;
typedef  TYPE_5__ serf_status_line ;
typedef  int /*<<< orphan*/  serf_request_t ;
typedef  int /*<<< orphan*/  serf_bucket_t ;
typedef  scalar_t__ apr_status_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_20__ {int last_status_code; } ;
struct TYPE_19__ {int /*<<< orphan*/ * auth_state; scalar_t__ auth_attempts; int /*<<< orphan*/  pool; int /*<<< orphan*/  session_url_str; void* http20; void* http10; } ;

/* Variables and functions */
 scalar_t__ APR_STATUS_IS_ECONNABORTED (scalar_t__) ; 
 scalar_t__ APR_STATUS_IS_ECONNRESET (scalar_t__) ; 
 int /*<<< orphan*/  APR_STATUS_IS_EOF (scalar_t__) ; 
 scalar_t__ APR_SUCCESS ; 
 void* FALSE ; 
 int /*<<< orphan*/  SERF_BUCKET_READ_ERROR (scalar_t__) ; 
 scalar_t__ SERF_HTTP_10 ; 
 scalar_t__ SERF_HTTP_VERSION (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 int /*<<< orphan*/  SVN_ERR_RA_DAV_MALFORMED_DATA ; 
 int /*<<< orphan*/  SVN_ERR_RA_DAV_REQUEST_FAILED ; 
 TYPE_4__* SVN_NO_ERROR ; 
 void* TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  apr_pstrdup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ drain_bucket (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  response_get_location (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* serf_bucket_headers_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * serf_bucket_response_get_headers (int /*<<< orphan*/ *) ; 
 scalar_t__ serf_bucket_response_status (int /*<<< orphan*/ *,TYPE_5__*) ; 
 scalar_t__ serf_bucket_response_wait_for_headers (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ strncasecmp (char const*,char*,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* stub2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_auth_save_credentials (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_4__*) ; 
 TYPE_4__* svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,...) ; 
 TYPE_4__* svn_error_trace (TYPE_4__*) ; 
 TYPE_4__* svn_ra_serf__handle_server_error (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_serf__request_create (TYPE_3__*) ; 
 int /*<<< orphan*/  svn_ra_serf__setup_error_parsing (int /*<<< orphan*/ **,TYPE_3__*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_ra_serf__wrap_err (scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
handle_response(serf_request_t *request,
                serf_bucket_t *response,
                svn_ra_serf__handler_t *handler,
                apr_status_t *serf_status,
                apr_pool_t *scratch_pool)
{
  apr_status_t status;
  svn_error_t *err;

  /* ### need to verify whether this already gets init'd on every
     ### successful exit. for an error-exit, it will (properly) be
     ### ignored by the caller.  */
  *serf_status = APR_SUCCESS;

  if (!response)
    {
      /* Uh-oh. Our connection died.  */
      handler->scheduled = FALSE;

      if (handler->response_error)
        {
          /* Give a handler chance to prevent request requeue. */
          SVN_ERR(handler->response_error(request, response, 0,
                                          handler->response_error_baton));

          svn_ra_serf__request_create(handler);
        }
      /* Response error callback is not configured. Requeue another request
         for this handler only if we didn't started to process body.
         Return error otherwise. */
      else if (!handler->reading_body)
        {
          svn_ra_serf__request_create(handler);
        }
      else
        {
          return svn_error_createf(SVN_ERR_RA_DAV_REQUEST_FAILED, NULL,
                                    _("%s request on '%s' failed"),
                                   handler->method, handler->path);
        }

      return SVN_NO_ERROR;
    }

  /* If we're reading the body, then skip all this preparation.  */
  if (handler->reading_body)
    goto process_body;

  /* Copy the Status-Line info into HANDLER, if we don't yet have it.  */
  if (handler->sline.version == 0)
    {
      serf_status_line sl;

      status = serf_bucket_response_status(response, &sl);
      if (status != APR_SUCCESS)
        {
          /* The response line is not (yet) ready, or some other error.  */
          *serf_status = status;
          return SVN_NO_ERROR; /* Handled by serf */
        }

      /* If we got APR_SUCCESS, then we should have Status-Line info.  */
      SVN_ERR_ASSERT(sl.version != 0);

      handler->sline = sl;
      handler->sline.reason = apr_pstrdup(handler->handler_pool, sl.reason);

      /* HTTP/1.1? (or later)  */
      if (sl.version != SERF_HTTP_10)
        handler->session->http10 = FALSE;

      if (sl.version >= SERF_HTTP_VERSION(2, 0)) {
        handler->session->http20 = TRUE;
      }
    }

  /* Keep reading from the network until we've read all the headers.  */
  status = serf_bucket_response_wait_for_headers(response);
  if (status)
    {
      /* The typical "error" will be APR_EAGAIN, meaning that more input
         from the network is required to complete the reading of the
         headers.  */
      if (!APR_STATUS_IS_EOF(status))
        {
          /* Either the headers are not (yet) complete, or there really
             was an error.  */
          *serf_status = status;
          return SVN_NO_ERROR;
        }

      /* wait_for_headers() will return EOF if there is no body in this
         response, or if we completely read the body. The latter is not
         true since we would have set READING_BODY to get the body read,
         and we would not be back to this code block.

         It can also return EOF if we truly hit EOF while (say) processing
         the headers. aka Badness.  */

      /* Cases where a lack of a response body (via EOF) is okay:
       *  - A HEAD request
       *  - 204/304 response
       *
       * Otherwise, if we get an EOF here, something went really wrong: either
       * the server closed on us early or we're reading too much.  Either way,
       * scream loudly.
       */
      if (strcmp(handler->method, "HEAD") != 0
          && handler->sline.code != 204
          && handler->sline.code != 304)
        {
          err = svn_error_createf(SVN_ERR_RA_DAV_MALFORMED_DATA,
                                  svn_ra_serf__wrap_err(status, NULL),
                                  _("Premature EOF seen from server"
                                    " (http status=%d)"),
                                  handler->sline.code);

          /* In case anything else arrives... discard it.  */
          handler->discard_body = TRUE;

          return err;
        }
    }

  /* ... and set up the header fields in HANDLER.  */
  handler->location = response_get_location(response,
                                            handler->session->session_url_str,
                                            handler->handler_pool,
                                            scratch_pool);

  /* On the last request, we failed authentication. We succeeded this time,
     so let's save away these credentials.  */
  if (handler->conn->last_status_code == 401 && handler->sline.code < 400)
    {
      SVN_ERR(svn_auth_save_credentials(handler->session->auth_state,
                                        handler->session->pool));
      handler->session->auth_attempts = 0;
      handler->session->auth_state = NULL;
    }
  handler->conn->last_status_code = handler->sline.code;

  if (handler->sline.code >= 400)
    {
      /* 405 Method Not allowed.
         408 Request Timeout
         409 Conflict: can indicate a hook error.
         5xx (Internal) Server error. */
      serf_bucket_t *hdrs;
      const char *val;

      hdrs = serf_bucket_response_get_headers(response);
      val = serf_bucket_headers_get(hdrs, "Content-Type");
      if (val && strncasecmp(val, "text/xml", sizeof("text/xml") - 1) == 0)
        {
          svn_ra_serf__server_error_t *server_err;

          SVN_ERR(svn_ra_serf__setup_error_parsing(&server_err, handler,
                                                   FALSE,
                                                   handler->handler_pool,
                                                   handler->handler_pool));

          handler->server_error = server_err;
        }
      else
        {
          handler->discard_body = TRUE;
        }
    }
  else if (handler->sline.code <= 199)
    {
      handler->discard_body = TRUE;
    }

  /* Stop processing the above, on every packet arrival.  */
  handler->reading_body = TRUE;

 process_body:

  /* We've been instructed to ignore the body. Drain whatever is present.  */
  if (handler->discard_body)
    {
      *serf_status = drain_bucket(response);

      return SVN_NO_ERROR;
    }

  /* If we are supposed to parse the body as a server_error, then do
     that now.  */
  if (handler->server_error != NULL)
    {
      return svn_error_trace(
                svn_ra_serf__handle_server_error(handler->server_error,
                                                 handler,
                                                 request, response,
                                                 serf_status,
                                                 scratch_pool));
    }

  /* Pass the body along to the registered response handler.  */
  err = handler->response_handler(request, response,
                                  handler->response_baton,
                                  scratch_pool);

  if (err
      && (!SERF_BUCKET_READ_ERROR(err->apr_err)
          || APR_STATUS_IS_ECONNRESET(err->apr_err)
          || APR_STATUS_IS_ECONNABORTED(err->apr_err)))
    {
      /* These errors are special cased in serf
         ### We hope no handler returns these by accident. */
      *serf_status = err->apr_err;
      svn_error_clear(err);
      return SVN_NO_ERROR;
    }

  return svn_error_trace(err);
}