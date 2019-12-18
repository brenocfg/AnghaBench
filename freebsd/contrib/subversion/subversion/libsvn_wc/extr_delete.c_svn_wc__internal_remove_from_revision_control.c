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
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_WC_LEFT_LOCAL_MOD ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 char const* svn_dirent_dirname (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_io_dir_remove_nonrecursive (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__adm_destroy (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_is_wcroot (scalar_t__*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_op_remove_node (scalar_t__*,int /*<<< orphan*/ *,char const*,scalar_t__,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__wq_run (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__write_check (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc__internal_remove_from_revision_control(svn_wc__db_t *db,
                                              const char *local_abspath,
                                              svn_boolean_t destroy_wf,
                                              svn_cancel_func_t cancel_func,
                                              void *cancel_baton,
                                              apr_pool_t *scratch_pool)
{
  svn_boolean_t left_something = FALSE;
  svn_boolean_t is_root;
  svn_error_t *err = NULL;

  SVN_ERR(svn_wc__db_is_wcroot(&is_root, db, local_abspath, scratch_pool));

  SVN_ERR(svn_wc__write_check(db, is_root ? local_abspath
                                          : svn_dirent_dirname(local_abspath,
                                                               scratch_pool),
                              scratch_pool));

  SVN_ERR(svn_wc__db_op_remove_node(&left_something,
                                    db, local_abspath,
                                    destroy_wf /* destroy_wc */,
                                    destroy_wf /* destroy_changes */,
                                    NULL, NULL,
                                    cancel_func, cancel_baton,
                                    scratch_pool));

  SVN_ERR(svn_wc__wq_run(db, local_abspath,
                         cancel_func, cancel_baton,
                         scratch_pool));

  if (is_root)
    {
      /* Destroy the administrative area */
      SVN_ERR(svn_wc__adm_destroy(db, local_abspath, cancel_func, cancel_baton,
                                  scratch_pool));

      /* And if we didn't leave something interesting, remove the directory */
      if (!left_something && destroy_wf)
        err = svn_io_dir_remove_nonrecursive(local_abspath, scratch_pool);
    }

  if (left_something || err)
    return svn_error_create(SVN_ERR_WC_LEFT_LOCAL_MOD, err, NULL);

  return SVN_NO_ERROR;
}