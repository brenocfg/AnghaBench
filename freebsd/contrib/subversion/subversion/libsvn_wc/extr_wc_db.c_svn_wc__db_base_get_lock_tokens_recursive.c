#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  wc_id; int /*<<< orphan*/  sdb; } ;
typedef  TYPE_1__ svn_wc__db_wcroot_t ;
typedef  int /*<<< orphan*/  svn_wc__db_t ;
typedef  int /*<<< orphan*/  svn_sqlite__stmt_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  scalar_t__ apr_int64_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 scalar_t__ INVALID_REPOS_ID ; 
 int /*<<< orphan*/  STMT_SELECT_BASE_NODE_LOCK_TOKENS_RECURSIVE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VERIFY_USABLE_WCROOT (TYPE_1__*) ; 
 int /*<<< orphan*/ * apr_hash_make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_is_absolute (char const*) ; 
 int /*<<< orphan*/  svn_error_compose_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  svn_path_url_add_component2 (char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__bindf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ svn_sqlite__column_int64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* svn_sqlite__column_text (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__get_statement (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_sqlite__reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__step (scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_wc__db_fetch_repos_info (char const**,int /*<<< orphan*/ *,TYPE_1__*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_wcroot_parse_local_abspath (TYPE_1__**,char const**,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc__db_base_get_lock_tokens_recursive(apr_hash_t **lock_tokens,
                                          svn_wc__db_t *db,
                                          const char *local_abspath,
                                          apr_pool_t *result_pool,
                                          apr_pool_t *scratch_pool)
{
  svn_wc__db_wcroot_t *wcroot;
  const char *local_relpath;
  svn_sqlite__stmt_t *stmt;
  svn_boolean_t have_row;
  apr_int64_t last_repos_id = INVALID_REPOS_ID;
  const char *last_repos_root_url = NULL;

  SVN_ERR_ASSERT(svn_dirent_is_absolute(local_abspath));

  SVN_ERR(svn_wc__db_wcroot_parse_local_abspath(&wcroot, &local_relpath,
                                                db, local_abspath,
                                                scratch_pool, scratch_pool));
  VERIFY_USABLE_WCROOT(wcroot);

  *lock_tokens = apr_hash_make(result_pool);

  /* Fetch all the lock tokens in and under LOCAL_RELPATH. */
  SVN_ERR(svn_sqlite__get_statement(
              &stmt, wcroot->sdb,
              STMT_SELECT_BASE_NODE_LOCK_TOKENS_RECURSIVE));

  SVN_ERR(svn_sqlite__bindf(stmt, "is", wcroot->wc_id, local_relpath));
  SVN_ERR(svn_sqlite__step(&have_row, stmt));
  while (have_row)
    {
      apr_int64_t child_repos_id = svn_sqlite__column_int64(stmt, 0);
      const char *child_relpath = svn_sqlite__column_text(stmt, 1, NULL);
      const char *lock_token = svn_sqlite__column_text(stmt, 2, result_pool);

      if (child_repos_id != last_repos_id)
        {
          svn_error_t *err = svn_wc__db_fetch_repos_info(&last_repos_root_url,
                                                         NULL, wcroot,
                                                         child_repos_id,
                                                         scratch_pool);

          if (err)
            {
              return svn_error_trace(
                            svn_error_compose_create(err,
                                                     svn_sqlite__reset(stmt)));
            }

          last_repos_id = child_repos_id;
        }

      SVN_ERR_ASSERT(last_repos_root_url != NULL);
      svn_hash_sets(*lock_tokens,
                    svn_path_url_add_component2(last_repos_root_url,
                                                child_relpath, result_pool),
                    lock_token);

      SVN_ERR(svn_sqlite__step(&have_row, stmt));
    }
  return svn_sqlite__reset(stmt);
}