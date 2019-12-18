#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {TYPE_3__* err; } ;
typedef  TYPE_2__ svn_wc_notify_t ;
struct TYPE_15__ {scalar_t__ apr_err; } ;
typedef  TYPE_3__ svn_error_t ;
struct revert_with_write_lock_baton {TYPE_1__* ctx; int /*<<< orphan*/  local_abspath; int /*<<< orphan*/  metadata_only; int /*<<< orphan*/  clear_changelists; int /*<<< orphan*/  changelists; int /*<<< orphan*/  use_commit_times; int /*<<< orphan*/  depth; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_13__ {int /*<<< orphan*/  notify_baton2; int /*<<< orphan*/  (* notify_func2 ) (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  cancel_baton; int /*<<< orphan*/  cancel_func; int /*<<< orphan*/  wc_ctx; } ;

/* Variables and functions */
 scalar_t__ SVN_ERR_ENTRY_NOT_FOUND ; 
 scalar_t__ SVN_ERR_UNVERSIONED_RESOURCE ; 
 scalar_t__ SVN_ERR_WC_PATH_NOT_FOUND ; 
 TYPE_3__* SVN_NO_ERROR ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_3__*) ; 
 TYPE_3__* svn_error_trace (TYPE_3__*) ; 
 TYPE_2__* svn_wc_create_notify (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_notify_skip ; 
 TYPE_3__* svn_wc_revert5 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *),int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
revert(void *baton, apr_pool_t *result_pool, apr_pool_t *scratch_pool)
{
  struct revert_with_write_lock_baton *b = baton;
  svn_error_t *err;

  err = svn_wc_revert5(b->ctx->wc_ctx,
                       b->local_abspath,
                       b->depth,
                       b->use_commit_times,
                       b->changelists,
                       b->clear_changelists,
                       b->metadata_only,
                       b->ctx->cancel_func, b->ctx->cancel_baton,
                       b->ctx->notify_func2, b->ctx->notify_baton2,
                       scratch_pool);

  if (err)
    {
      /* If target isn't versioned, just send a 'skip'
         notification and move on. */
      if (err->apr_err == SVN_ERR_ENTRY_NOT_FOUND
          || err->apr_err == SVN_ERR_UNVERSIONED_RESOURCE
          || err->apr_err == SVN_ERR_WC_PATH_NOT_FOUND)
        {
          if (b->ctx->notify_func2)
            {
              svn_wc_notify_t *notify;

              notify = svn_wc_create_notify(b->local_abspath,
                                            svn_wc_notify_skip,
                                            scratch_pool);

              notify->err = err;

              b->ctx->notify_func2(b->ctx->notify_baton2,
                                   notify, scratch_pool);
            }
          svn_error_clear(err);
        }
      else
        return svn_error_trace(err);
    }

  return SVN_NO_ERROR;
}