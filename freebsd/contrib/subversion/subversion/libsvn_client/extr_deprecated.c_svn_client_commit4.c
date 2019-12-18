#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_depth_t ;
typedef  int /*<<< orphan*/  svn_commit_info_t ;
struct TYPE_4__ {struct downgrade_commit_copied_notify_baton* notify_baton2; int /*<<< orphan*/  notify_func2; } ;
typedef  TYPE_1__ svn_client_ctx_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct downgrade_commit_copied_notify_baton {struct downgrade_commit_copied_notify_baton* orig_notify_baton2; int /*<<< orphan*/  orig_notify_func2; } ;
struct capture_baton_t {int /*<<< orphan*/ * pool; int /*<<< orphan*/ ** info; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  capture_commit_info ; 
 int /*<<< orphan*/  downgrade_commit_copied_notify_func ; 
 int /*<<< orphan*/ * svn_client_commit5 (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,struct capture_baton_t*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_create_commit_info (int /*<<< orphan*/ *) ; 

svn_error_t *
svn_client_commit4(svn_commit_info_t **commit_info_p,
                   const apr_array_header_t *targets,
                   svn_depth_t depth,
                   svn_boolean_t keep_locks,
                   svn_boolean_t keep_changelists,
                   const apr_array_header_t *changelists,
                   const apr_hash_t *revprop_table,
                   svn_client_ctx_t *ctx,
                   apr_pool_t *pool)
{
  struct capture_baton_t cb;
  struct downgrade_commit_copied_notify_baton notify_baton;
  svn_error_t *err;

  notify_baton.orig_notify_func2 = ctx->notify_func2;
  notify_baton.orig_notify_baton2 = ctx->notify_baton2;

  *commit_info_p = NULL;
  cb.info = commit_info_p;
  cb.pool = pool;

  /* Swap out the notification system (if any) with a thin filtering
     wrapper. */
  if (ctx->notify_func2)
    {
      ctx->notify_func2 = downgrade_commit_copied_notify_func;
      ctx->notify_baton2 = &notify_baton;
    }

  err = svn_client_commit5(targets, depth, keep_locks, keep_changelists, FALSE,
                           changelists, revprop_table,
                           capture_commit_info, &cb, ctx, pool);

  /* Ensure that the original notification system is in place. */
  ctx->notify_func2 = notify_baton.orig_notify_func2;
  ctx->notify_baton2 = notify_baton.orig_notify_baton2;

  SVN_ERR(err);

  if (! *commit_info_p)
    *commit_info_p = svn_create_commit_info(pool);

  return SVN_NO_ERROR;
}