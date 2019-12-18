#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  path; } ;
struct TYPE_12__ {int /*<<< orphan*/  using_chunked_requests; TYPE_2__ session_url; } ;
typedef  TYPE_3__ svn_ra_serf__session_t ;
struct TYPE_10__ {int code; } ;
struct TYPE_13__ {char* method; TYPE_1__ sline; int /*<<< orphan*/  no_fail_on_http_failure_status; int /*<<< orphan*/  body_delegate; int /*<<< orphan*/  response_handler; int /*<<< orphan*/  path; } ;
typedef  TYPE_4__ svn_ra_serf__handler_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  create_simple_options_body ; 
 int /*<<< orphan*/  svn_ra_serf__context_run_one (TYPE_4__*,int /*<<< orphan*/ *) ; 
 TYPE_4__* svn_ra_serf__create_handler (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_serf__handle_discard_body ; 
 int /*<<< orphan*/  svn_ra_serf__unexpected_status (TYPE_4__*) ; 

svn_error_t *
svn_ra_serf__probe_proxy(svn_ra_serf__session_t *serf_sess,
                         apr_pool_t *scratch_pool)
{
  svn_ra_serf__handler_t *handler;

  handler = svn_ra_serf__create_handler(serf_sess, scratch_pool);
  handler->method = "OPTIONS";
  handler->path = serf_sess->session_url.path;

  /* We don't care about the response body, so discard it.  */
  handler->response_handler = svn_ra_serf__handle_discard_body;

  /* We need a simple body, in order to send it in chunked format.  */
  handler->body_delegate = create_simple_options_body;
  handler->no_fail_on_http_failure_status = TRUE;

  /* No special headers.  */

  SVN_ERR(svn_ra_serf__context_run_one(handler, scratch_pool));
  /* Some versions of nginx in reverse proxy mode will return 411. They want
     a Content-Length header, rather than chunked requests. We can keep other
     HTTP/1.1 features, but will disable the chunking.  */
  if (handler->sline.code == 411)
    {
      serf_sess->using_chunked_requests = FALSE;

      return SVN_NO_ERROR;
    }
  if (handler->sline.code != 200)
    SVN_ERR(svn_ra_serf__unexpected_status(handler));

  return SVN_NO_ERROR;
}