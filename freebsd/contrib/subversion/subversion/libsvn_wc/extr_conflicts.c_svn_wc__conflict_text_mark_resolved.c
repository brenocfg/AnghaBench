#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  (* svn_wc_notify_func2_t ) (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;
struct TYPE_3__ {int /*<<< orphan*/  db; } ;
typedef  TYPE_1__ svn_wc_context_t ;
typedef  int /*<<< orphan*/  svn_wc_conflict_choice_t ;
typedef  int /*<<< orphan*/  svn_skel_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_cancel_func_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  build_text_conflict_resolve_items (int /*<<< orphan*/ **,scalar_t__*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_op_mark_resolved (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_read_conflict (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__wq_run (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_create_notify (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_notify_resolved_text ; 

svn_error_t *
svn_wc__conflict_text_mark_resolved(svn_wc_context_t *wc_ctx,
                                    const char *local_abspath,
                                    svn_wc_conflict_choice_t choice,
                                    svn_cancel_func_t cancel_func,
                                    void *cancel_baton,
                                    svn_wc_notify_func2_t notify_func,
                                    void *notify_baton,
                                    apr_pool_t *scratch_pool)
{
  svn_skel_t *work_items;
  svn_skel_t *conflict;
  svn_boolean_t did_resolve;

  SVN_ERR(svn_wc__db_read_conflict(&conflict, NULL, NULL,
                                   wc_ctx->db, local_abspath,
                                   scratch_pool, scratch_pool));

  if (!conflict)
    return SVN_NO_ERROR;

  SVN_ERR(build_text_conflict_resolve_items(&work_items, &did_resolve,
                                            wc_ctx->db, local_abspath,
                                            conflict, choice,
                                            NULL, FALSE, NULL,
                                            cancel_func, cancel_baton,
                                            scratch_pool, scratch_pool));

  SVN_ERR(svn_wc__db_op_mark_resolved(wc_ctx->db, local_abspath,
                                      TRUE, FALSE, FALSE,
                                      work_items, scratch_pool));

  SVN_ERR(svn_wc__wq_run(wc_ctx->db, local_abspath,
                         cancel_func, cancel_baton,
                         scratch_pool));

  if (did_resolve && notify_func)
    notify_func(notify_baton,
                svn_wc_create_notify(local_abspath,
                                     svn_wc_notify_resolved_text,
                                     scratch_pool),
                scratch_pool);

  return SVN_NO_ERROR;
}