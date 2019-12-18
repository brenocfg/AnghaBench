#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int code; } ;
struct TYPE_12__ {char* method; TYPE_2__ sline; int /*<<< orphan*/ * path; int /*<<< orphan*/  no_fail_on_http_failure_status; struct TYPE_12__* response_baton; int /*<<< orphan*/  response_handler; } ;
typedef  TYPE_3__ svn_ra_serf__handler_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_13__ {int /*<<< orphan*/ * txn_url; int /*<<< orphan*/ * activity_url; TYPE_7__* session; } ;
typedef  TYPE_4__ commit_context_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_14__ {TYPE_1__** conns; } ;
struct TYPE_10__ {int /*<<< orphan*/  conn; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ USING_HTTPV2_COMMIT_SUPPORT (TYPE_4__*) ; 
 int /*<<< orphan*/  serf_connection_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_ra_serf__context_run_one (TYPE_3__*,int /*<<< orphan*/ *) ; 
 TYPE_3__* svn_ra_serf__create_handler (TYPE_7__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_serf__expect_empty_body ; 
 int /*<<< orphan*/  svn_ra_serf__unexpected_status (TYPE_3__*) ; 

__attribute__((used)) static svn_error_t *
abort_edit(void *edit_baton,
           apr_pool_t *pool)
{
  commit_context_t *ctx = edit_baton;
  svn_ra_serf__handler_t *handler;

  /* If an activity or transaction wasn't even created, don't bother
     trying to delete it. */
  if (! (ctx->activity_url || ctx->txn_url))
    return SVN_NO_ERROR;

  /* An error occurred on conns[0]. serf 0.4.0 remembers that the connection
     had a problem. We need to reset it, in order to use it again.  */
  serf_connection_reset(ctx->session->conns[0]->conn);

  /* DELETE our aborted activity */
  handler = svn_ra_serf__create_handler(ctx->session, pool);

  handler->method = "DELETE";

  handler->response_handler = svn_ra_serf__expect_empty_body;
  handler->response_baton = handler;
  handler->no_fail_on_http_failure_status = TRUE;

  if (USING_HTTPV2_COMMIT_SUPPORT(ctx)) /* HTTP v2 */
    handler->path = ctx->txn_url;
  else
    handler->path = ctx->activity_url;

  SVN_ERR(svn_ra_serf__context_run_one(handler, pool));

  /* 204 if deleted,
     403 if DELETE was forbidden (indicates MKACTIVITY was forbidden too),
     404 if the activity wasn't found. */
  if (handler->sline.code != 204
      && handler->sline.code != 403
      && handler->sline.code != 404)
    {
      return svn_error_trace(svn_ra_serf__unexpected_status(handler));
    }

  /* Don't delete again if somebody aborts twice */
  ctx->activity_url = NULL;
  ctx->txn_url = NULL;

  return SVN_NO_ERROR;
}