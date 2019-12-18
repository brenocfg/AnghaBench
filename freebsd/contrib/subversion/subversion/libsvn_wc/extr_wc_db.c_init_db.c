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
typedef  int /*<<< orphan*/  svn_wc__db_status_t ;
typedef  int /*<<< orphan*/  svn_sqlite__stmt_t ;
typedef  int /*<<< orphan*/  svn_sqlite__db_t ;
typedef  scalar_t__ svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_depth_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  STMT_CREATE_SCHEMA ; 
 int /*<<< orphan*/  STMT_INSERT_NODE ; 
 int /*<<< orphan*/  STMT_INSERT_WCROOT ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_VA_NULL ; 
 int /*<<< orphan*/  create_repos_id (int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  depth_map ; 
 int /*<<< orphan*/  kind_map ; 
 int /*<<< orphan*/  presence_map ; 
 int /*<<< orphan*/  svn_node_dir ; 
 int /*<<< orphan*/  svn_sqlite__bindf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_sqlite__exec_statements (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_sqlite__get_statement (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_sqlite__insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_token__to_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_wc__db_install_schema_statistics (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_status_incomplete ; 
 int /*<<< orphan*/  svn_wc__db_status_normal ; 

__attribute__((used)) static svn_error_t *
init_db(/* output values */
        apr_int64_t *repos_id,
        apr_int64_t *wc_id,
        /* input values */
        svn_sqlite__db_t *db,
        const char *repos_root_url,
        const char *repos_uuid,
        const char *root_node_repos_relpath,
        svn_revnum_t root_node_revision,
        svn_depth_t root_node_depth,
        apr_pool_t *scratch_pool)
{
  svn_sqlite__stmt_t *stmt;

  /* Create the database's schema.  */
  SVN_ERR(svn_sqlite__exec_statements(db, STMT_CREATE_SCHEMA));

  SVN_ERR(svn_wc__db_install_schema_statistics(db, scratch_pool));

  /* Insert the repository. */
  SVN_ERR(create_repos_id(repos_id, repos_root_url, repos_uuid,
                          db, scratch_pool));

  /* Insert the wcroot. */
  /* ### Right now, this just assumes wc metadata is being stored locally. */
  SVN_ERR(svn_sqlite__get_statement(&stmt, db, STMT_INSERT_WCROOT));
  SVN_ERR(svn_sqlite__insert(wc_id, stmt));

  if (root_node_repos_relpath)
    {
      svn_wc__db_status_t status = svn_wc__db_status_normal;

      if (root_node_revision > 0)
        status = svn_wc__db_status_incomplete; /* Will be filled by update */

      SVN_ERR(svn_sqlite__get_statement(&stmt, db, STMT_INSERT_NODE));
      SVN_ERR(svn_sqlite__bindf(stmt, "isdsisrtst",
                                *wc_id,              /* 1 */
                                "",                  /* 2 */
                                0,                   /* op_depth is 0 for base */
                                SVN_VA_NULL,         /* 4 */
                                *repos_id,
                                root_node_repos_relpath,
                                root_node_revision,
                                presence_map, status, /* 8 */
                                svn_token__to_word(depth_map,
                                                   root_node_depth),
                                kind_map, svn_node_dir /* 10 */));

      SVN_ERR(svn_sqlite__insert(NULL, stmt));
    }

  return SVN_NO_ERROR;
}