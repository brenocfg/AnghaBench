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
typedef  int /*<<< orphan*/  svn_sqlite__db_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_depth_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_int64_t ;
typedef  int /*<<< orphan*/  apr_int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_SQLITE__WITH_LOCK (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_db (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__mode_rwcreate ; 
 int /*<<< orphan*/  svn_wc__db_util_open_db (int /*<<< orphan*/ **,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
create_db(svn_sqlite__db_t **sdb,
          apr_int64_t *repos_id,
          apr_int64_t *wc_id,
          const char *dir_abspath,
          const char *repos_root_url,
          const char *repos_uuid,
          const char *sdb_fname,
          const char *root_node_repos_relpath,
          svn_revnum_t root_node_revision,
          svn_depth_t root_node_depth,
          svn_boolean_t exclusive,
          apr_int32_t timeout,
          apr_pool_t *result_pool,
          apr_pool_t *scratch_pool)
{
  SVN_ERR(svn_wc__db_util_open_db(sdb, dir_abspath, sdb_fname,
                                  svn_sqlite__mode_rwcreate, exclusive,
                                  timeout,
                                  NULL /* my_statements */,
                                  result_pool, scratch_pool));

  SVN_SQLITE__WITH_LOCK(init_db(repos_id, wc_id,
                                *sdb, repos_root_url, repos_uuid,
                                root_node_repos_relpath, root_node_revision,
                                root_node_depth, scratch_pool),
                        *sdb);

  return SVN_NO_ERROR;
}