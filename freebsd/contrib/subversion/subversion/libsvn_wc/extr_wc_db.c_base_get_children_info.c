#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  wc_id; int /*<<< orphan*/  sdb; } ;
typedef  TYPE_1__ svn_wc__db_wcroot_t ;
typedef  int /*<<< orphan*/  svn_sqlite__stmt_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
struct svn_wc__db_base_info_t {char const* repos_root_url; int /*<<< orphan*/  lock; int /*<<< orphan*/  update_root; int /*<<< orphan*/  depth; int /*<<< orphan*/  revnum; void* kind; void* status; void* repos_relpath; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  scalar_t__ apr_int64_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 scalar_t__ INVALID_REPOS_ID ; 
 int /*<<< orphan*/  STMT_SELECT_BASE_CHILDREN_INFO ; 
 int /*<<< orphan*/  STMT_SELECT_BASE_CHILDREN_INFO_LOCK ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * apr_hash_make (int /*<<< orphan*/ *) ; 
 struct svn_wc__db_base_info_t* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  depth_map ; 
 int /*<<< orphan*/  kind_map ; 
 int /*<<< orphan*/  lock_from_columns (int /*<<< orphan*/ *,int,int,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  presence_map ; 
 int /*<<< orphan*/  svn_depth_unknown ; 
 int /*<<< orphan*/  svn_error_compose_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ *,char const*,struct svn_wc__db_base_info_t*) ; 
 char* svn_relpath_basename (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__bindf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  svn_sqlite__column_boolean (int /*<<< orphan*/ *,int) ; 
 scalar_t__ svn_sqlite__column_int64 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  svn_sqlite__column_revnum (int /*<<< orphan*/ *,int) ; 
 void* svn_sqlite__column_text (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 void* svn_sqlite__column_token (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_sqlite__column_token_null (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_sqlite__get_statement (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_sqlite__reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__step (scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_wc__db_fetch_repos_info (char const**,int /*<<< orphan*/ *,TYPE_1__*,scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
base_get_children_info(apr_hash_t **nodes,
                       svn_wc__db_wcroot_t *wcroot,
                       const char *local_relpath,
                       svn_boolean_t obtain_locks,
                       apr_pool_t *result_pool,
                       apr_pool_t *scratch_pool)
{
  svn_sqlite__stmt_t *stmt;
  svn_boolean_t have_row;
  apr_int64_t last_repos_id = INVALID_REPOS_ID;
  const char *last_repos_root_url = NULL;

  *nodes = apr_hash_make(result_pool);

  SVN_ERR(svn_sqlite__get_statement(&stmt, wcroot->sdb,
                                    obtain_locks
                                      ? STMT_SELECT_BASE_CHILDREN_INFO_LOCK
                                      : STMT_SELECT_BASE_CHILDREN_INFO));
  SVN_ERR(svn_sqlite__bindf(stmt, "is", wcroot->wc_id, local_relpath));

  SVN_ERR(svn_sqlite__step(&have_row, stmt));

  while (have_row)
    {
      struct svn_wc__db_base_info_t *info;
      apr_int64_t repos_id;
      const char *child_relpath = svn_sqlite__column_text(stmt, 0, NULL);
      const char *name = svn_relpath_basename(child_relpath, result_pool);

      info = apr_pcalloc(result_pool, sizeof(*info));

      repos_id = svn_sqlite__column_int64(stmt, 1);
      info->repos_relpath = svn_sqlite__column_text(stmt, 2, result_pool);
      info->status = svn_sqlite__column_token(stmt, 3, presence_map);
      info->kind = svn_sqlite__column_token(stmt, 4, kind_map);
      info->revnum = svn_sqlite__column_revnum(stmt, 5);

      info->depth = svn_sqlite__column_token_null(stmt, 6, depth_map,
                                                  svn_depth_unknown);

      info->update_root = svn_sqlite__column_boolean(stmt, 7);

      if (obtain_locks)
        info->lock = lock_from_columns(stmt, 8, 9, 10, 11, result_pool);

      if (repos_id != last_repos_id)
        {
          svn_error_t *err;

          err = svn_wc__db_fetch_repos_info(&last_repos_root_url, NULL,
                                            wcroot, repos_id,
                                            result_pool);

          if (err)
            return svn_error_trace(
                     svn_error_compose_create(err,
                                              svn_sqlite__reset(stmt)));

          last_repos_id = repos_id;
        }

      info->repos_root_url = last_repos_root_url;

      svn_hash_sets(*nodes, name, info);

      SVN_ERR(svn_sqlite__step(&have_row, stmt));
    }

  SVN_ERR(svn_sqlite__reset(stmt));

  return SVN_NO_ERROR;
}