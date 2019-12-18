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
typedef  int /*<<< orphan*/  svn_sqlite__mode_t ;
typedef  int /*<<< orphan*/  svn_sqlite__db_t ;
typedef  scalar_t__ svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_ENOENT ; 
 int /*<<< orphan*/  STMT_PRAGMA_LOCKING_MODE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  relpath_depth_sqlite ; 
 char const* const* statements ; 
 int /*<<< orphan*/  svn_dirent_local_style (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_io_check_path (char const*,scalar_t__*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_file ; 
 int /*<<< orphan*/  svn_sqlite__create_scalar_function (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__exec_statements (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_sqlite__mode_rwcreate ; 
 int /*<<< orphan*/  svn_sqlite__open (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ ,char const* const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* svn_wc__adm_child (char const*,char const*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc__db_util_open_db(svn_sqlite__db_t **sdb,
                        const char *dir_abspath,
                        const char *sdb_fname,
                        svn_sqlite__mode_t smode,
                        svn_boolean_t exclusive,
                        apr_int32_t timeout,
                        const char *const *my_statements,
                        apr_pool_t *result_pool,
                        apr_pool_t *scratch_pool)
{
  const char *sdb_abspath = svn_wc__adm_child(dir_abspath, sdb_fname,
                                              scratch_pool);

  if (smode != svn_sqlite__mode_rwcreate)
    {
      svn_node_kind_t kind;

      /* A file stat is much cheaper than a failed database open handled
         by SQLite. */
      SVN_ERR(svn_io_check_path(sdb_abspath, &kind, scratch_pool));

      if (kind != svn_node_file)
        return svn_error_createf(APR_ENOENT, NULL,
                                 _("Working copy database '%s' not found"),
                                 svn_dirent_local_style(sdb_abspath,
                                                        scratch_pool));
    }

  SVN_ERR(svn_sqlite__open(sdb, sdb_abspath, smode,
                           my_statements ? my_statements : statements,
                           0, NULL, timeout, result_pool, scratch_pool));

  if (exclusive)
    SVN_ERR(svn_sqlite__exec_statements(*sdb, STMT_PRAGMA_LOCKING_MODE));

  SVN_ERR(svn_sqlite__create_scalar_function(*sdb, "relpath_depth", 1,
                                             TRUE /* deterministic */,
                                             relpath_depth_sqlite, NULL));

  return SVN_NO_ERROR;
}