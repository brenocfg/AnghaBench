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
typedef  int /*<<< orphan*/  svn_cancel_func_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_dirent_is_absolute (char const*) ; 
 int /*<<< orphan*/  svn_io_remove_dir2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__adm_child (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_drop_root (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_is_wcroot (scalar_t__*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__write_check (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc__adm_destroy(svn_wc__db_t *db,
                    const char *dir_abspath,
                    svn_cancel_func_t cancel_func,
                    void *cancel_baton,
                    apr_pool_t *scratch_pool)
{
  svn_boolean_t is_wcroot;

  SVN_ERR_ASSERT(svn_dirent_is_absolute(dir_abspath));

  SVN_ERR(svn_wc__write_check(db, dir_abspath, scratch_pool));

  SVN_ERR(svn_wc__db_is_wcroot(&is_wcroot, db, dir_abspath, scratch_pool));

  /* Well, the coast is clear for blowing away the administrative
     directory, which also removes remaining locks */

  /* Now close the DB, and we can delete the working copy */
  if (is_wcroot)
    {
      SVN_ERR(svn_wc__db_drop_root(db, dir_abspath, scratch_pool));
      SVN_ERR(svn_io_remove_dir2(svn_wc__adm_child(dir_abspath, NULL,
                                                   scratch_pool),
                                 FALSE,
                                 cancel_func, cancel_baton,
                                 scratch_pool));
    }

  return SVN_NO_ERROR;
}