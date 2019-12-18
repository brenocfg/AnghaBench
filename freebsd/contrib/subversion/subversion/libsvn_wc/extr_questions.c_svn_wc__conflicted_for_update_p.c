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
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  internal_conflicted_p (int*,int*,int*,int*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc__conflicted_for_update_p(svn_boolean_t *conflicted_p,
                                svn_boolean_t *conflict_ignored_p,
                                svn_wc__db_t *db,
                                const char *local_abspath,
                                svn_boolean_t tree_only,
                                apr_pool_t *scratch_pool)
{
  svn_boolean_t text_conflicted, prop_conflicted, tree_conflicted;
  svn_boolean_t conflict_ignored;

  if (!conflict_ignored_p)
    conflict_ignored_p = &conflict_ignored;

  SVN_ERR(internal_conflicted_p(tree_only ? NULL: &text_conflicted,
                                tree_only ? NULL: &prop_conflicted,
                                &tree_conflicted, conflict_ignored_p,
                                db, local_abspath, scratch_pool));
  if (tree_only)
    *conflicted_p = tree_conflicted;
  else
    *conflicted_p = text_conflicted || prop_conflicted || tree_conflicted;

  return SVN_NO_ERROR;
}