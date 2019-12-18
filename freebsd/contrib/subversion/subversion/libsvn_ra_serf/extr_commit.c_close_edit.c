#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int code; } ;
struct TYPE_8__ {char* method; char* path; TYPE_1__ sline; struct TYPE_8__* response_baton; int /*<<< orphan*/  response_handler; } ;
typedef  TYPE_2__ svn_ra_serf__handler_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_commit_info_t ;
struct TYPE_9__ {char* activity_url; char* txn_url; scalar_t__ open_batons; int /*<<< orphan*/  session; int /*<<< orphan*/  callback_baton; int /*<<< orphan*/ * (* callback ) (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/  keep_locks; int /*<<< orphan*/  lock_tokens; } ;
typedef  TYPE_3__ commit_context_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SVN_ERR_FS_INCORRECT_EDITOR_COMPLETION ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_compose_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_ra_serf__context_run_one (TYPE_2__*,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_ra_serf__create_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_serf__expect_empty_body ; 
 int /*<<< orphan*/ * svn_ra_serf__run_merge (int /*<<< orphan*/  const**,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_serf__unexpected_status (TYPE_2__*) ; 

__attribute__((used)) static svn_error_t *
close_edit(void *edit_baton,
           apr_pool_t *pool)
{
  commit_context_t *ctx = edit_baton;
  const char *merge_target =
    ctx->activity_url ? ctx->activity_url : ctx->txn_url;
  const svn_commit_info_t *commit_info;
  svn_error_t *err = NULL;

  if (ctx->open_batons > 0)
    return svn_error_create(
              SVN_ERR_FS_INCORRECT_EDITOR_COMPLETION, NULL,
              _("Closing editor with directories or files open"));

  /* MERGE our activity */
  SVN_ERR(svn_ra_serf__run_merge(&commit_info,
                                 ctx->session,
                                 merge_target,
                                 ctx->lock_tokens,
                                 ctx->keep_locks,
                                 pool, pool));

  ctx->txn_url = NULL; /* If HTTPv2, the txn is now done */

  /* Inform the WC that we did a commit.  */
  if (ctx->callback)
    err = ctx->callback(commit_info, ctx->callback_baton, pool);

  /* If we're using activities, DELETE our completed activity.  */
  if (ctx->activity_url)
    {
      svn_ra_serf__handler_t *handler;

      handler = svn_ra_serf__create_handler(ctx->session, pool);

      handler->method = "DELETE";
      handler->path = ctx->activity_url;

      handler->response_handler = svn_ra_serf__expect_empty_body;
      handler->response_baton = handler;

      ctx->activity_url = NULL; /* Don't try again in abort_edit() on fail */

      SVN_ERR(svn_error_compose_create(
                  err,
                  svn_ra_serf__context_run_one(handler, pool)));

      if (handler->sline.code != 204)
        return svn_error_trace(svn_ra_serf__unexpected_status(handler));
    }

  SVN_ERR(err);

  return SVN_NO_ERROR;
}