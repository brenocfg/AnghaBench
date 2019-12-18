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
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  resolve_prop_conflict_on_node (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_wc__db_read_conflict (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_conflict_choose_merged ; 

svn_error_t *
svn_wc__mark_resolved_prop_conflicts(svn_wc__db_t *db,
                                     const char *local_abspath,
                                     apr_pool_t *scratch_pool)
{
  svn_boolean_t ignored_result;
  svn_skel_t *conflicts;

  SVN_ERR(svn_wc__db_read_conflict(&conflicts, NULL, NULL,
                                   db, local_abspath,
                                   scratch_pool, scratch_pool));

  if (!conflicts)
    return SVN_NO_ERROR;

  return svn_error_trace(resolve_prop_conflict_on_node(
                           &ignored_result,
                           db, local_abspath, conflicts, "",
                           svn_wc_conflict_choose_merged,
                           NULL, NULL,
                           NULL, NULL,
                           scratch_pool));
}