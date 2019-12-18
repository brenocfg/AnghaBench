#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  svn_wc__db_t ;
typedef  int /*<<< orphan*/  svn_skel_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_cancel_func_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  build_text_conflict_resolve_items (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_wc__db_op_mark_resolved (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_read_conflict (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__wq_run (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_conflict_choose_merged ; 

svn_error_t *
svn_wc__mark_resolved_text_conflict(svn_wc__db_t *db,
                                    const char *local_abspath,
                                    svn_cancel_func_t cancel_func,
                                    void *cancel_baton,
                                    apr_pool_t *scratch_pool)
{
  svn_skel_t *work_items;
  svn_skel_t *conflict;

  SVN_ERR(svn_wc__db_read_conflict(&conflict, NULL, NULL,
                                   db, local_abspath,
                                   scratch_pool, scratch_pool));

  if (!conflict)
    return SVN_NO_ERROR;

  SVN_ERR(build_text_conflict_resolve_items(&work_items, NULL,
                                            db, local_abspath, conflict,
                                            svn_wc_conflict_choose_merged,
                                            NULL, FALSE, NULL,
                                            cancel_func, cancel_baton,
                                            scratch_pool, scratch_pool));

  SVN_ERR(svn_wc__db_op_mark_resolved(db, local_abspath, TRUE, FALSE, FALSE,
                                      work_items, scratch_pool));

  return svn_error_trace(svn_wc__wq_run(db, local_abspath,
                                        cancel_func, cancel_baton,
                                        scratch_pool));
}