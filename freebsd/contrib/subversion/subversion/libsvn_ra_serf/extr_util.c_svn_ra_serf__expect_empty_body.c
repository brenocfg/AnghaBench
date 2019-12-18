#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_ra_serf__server_error_t ;
struct TYPE_4__ {int code; } ;
struct TYPE_5__ {int /*<<< orphan*/  discard_body; int /*<<< orphan*/ * server_error; int /*<<< orphan*/  handler_pool; TYPE_1__ sline; } ;
typedef  TYPE_2__ svn_ra_serf__handler_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  serf_request_t ;
typedef  int /*<<< orphan*/  serf_bucket_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 char* serf_bucket_headers_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * serf_bucket_response_get_headers (int /*<<< orphan*/ *) ; 
 scalar_t__ strncasecmp (char const*,char*,int) ; 
 int /*<<< orphan*/  svn_ra_serf__setup_error_parsing (int /*<<< orphan*/ **,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

svn_error_t *
svn_ra_serf__expect_empty_body(serf_request_t *request,
                               serf_bucket_t *response,
                               void *baton,
                               apr_pool_t *scratch_pool)
{
  svn_ra_serf__handler_t *handler = baton;
  serf_bucket_t *hdrs;
  const char *val;

  /* This function is just like handle_multistatus_only() except for the
     XML parsing callbacks. We want to look for the -readable element.  */

  /* We should see this just once, in order to initialize SERVER_ERROR.
     At that point, the core error processing will take over. If we choose
     not to parse an error, then we'll never return here (because we
     change the response handler).  */
  SVN_ERR_ASSERT(handler->server_error == NULL);

  hdrs = serf_bucket_response_get_headers(response);
  val = serf_bucket_headers_get(hdrs, "Content-Type");
  if (val
      && (handler->sline.code < 200 || handler->sline.code >= 300)
      && strncasecmp(val, "text/xml", sizeof("text/xml") - 1) == 0)
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
      /* The body was not text/xml, or we got a success code.
         Toss anything that arrives.  */
      handler->discard_body = TRUE;
    }

  /* Returning SVN_NO_ERROR will return APR_SUCCESS to serf, which tells it
     to call the response handler again. That will start up the XML parsing,
     or it will be dropped on the floor (per the decision above).  */
  return SVN_NO_ERROR;
}