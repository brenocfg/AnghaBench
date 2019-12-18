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
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ TRUE ; 
 char* svn_dirent_dirname (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_is_absolute (char const*) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__conflicted_for_update_p (scalar_t__*,scalar_t__*,int /*<<< orphan*/ *,char const*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_is_wcroot (scalar_t__*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
already_in_a_tree_conflict(svn_boolean_t *conflicted,
                           svn_boolean_t *ignored,
                           svn_wc__db_t *db,
                           const char *local_abspath,
                           apr_pool_t *scratch_pool)
{
  const char *ancestor_abspath = local_abspath;
  apr_pool_t *iterpool = svn_pool_create(scratch_pool);

  SVN_ERR_ASSERT(svn_dirent_is_absolute(local_abspath));

  *conflicted = *ignored = FALSE;

  while (TRUE)
    {
      svn_boolean_t is_wc_root;

      svn_pool_clear(iterpool);

      SVN_ERR(svn_wc__conflicted_for_update_p(conflicted, ignored, db,
                                              ancestor_abspath, TRUE,
                                              scratch_pool));
      if (*conflicted || *ignored)
        break;

      SVN_ERR(svn_wc__db_is_wcroot(&is_wc_root, db, ancestor_abspath,
                                   iterpool));
      if (is_wc_root)
        break;

      ancestor_abspath = svn_dirent_dirname(ancestor_abspath, scratch_pool);
    }

  svn_pool_destroy(iterpool);

  return SVN_NO_ERROR;
}