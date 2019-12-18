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
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_int64_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;

/* Variables and functions */
 int /*<<< orphan*/  STMT_COMMIT_UPDATE_ORIGIN ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 char* apr_hash_this_key (int /*<<< orphan*/ *) ; 
 char* apr_hash_this_val (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * moved_descendant_collect (int /*<<< orphan*/ **,TYPE_1__*,char const*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int relpath_depth (char const*) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 char* svn_relpath_join (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_relpath_skip_ancestor (char const*,char const*) ; 
 int /*<<< orphan*/ * svn_sqlite__bindf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_sqlite__get_statement (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_sqlite__update (int*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
moved_descendant_commit(svn_wc__db_wcroot_t *wcroot,
                        const char *local_relpath,
                        apr_int64_t repos_id,
                        const char *repos_relpath,
                        svn_revnum_t revision,
                        apr_hash_t *children,
                        apr_pool_t *scratch_pool)
{
  apr_pool_t *iterpool;
  svn_sqlite__stmt_t *stmt;
  apr_hash_index_t *hi;

  SVN_ERR_ASSERT(*local_relpath != '\0'
                 && *repos_relpath != '\0');

  if (!children)
    return SVN_NO_ERROR;

  /* Then update them */
  SVN_ERR(svn_sqlite__get_statement(&stmt, wcroot->sdb,
                                    STMT_COMMIT_UPDATE_ORIGIN));

  iterpool = svn_pool_create(scratch_pool);
  for (hi = apr_hash_first(scratch_pool, children); hi; hi = apr_hash_next(hi))
    {
      const char *src_relpath = apr_hash_this_val(hi);
      const char *to_relpath = apr_hash_this_key(hi);
      const char *new_repos_relpath;
      int to_op_depth = relpath_depth(to_relpath);
      int affected;
      apr_hash_t *map;

      svn_pool_clear(iterpool);

      SVN_ERR_ASSERT(to_op_depth > 0);

      new_repos_relpath = svn_relpath_join(
                            repos_relpath,
                            svn_relpath_skip_ancestor(local_relpath,
                                                      src_relpath),
                            iterpool);

      SVN_ERR(svn_sqlite__bindf(stmt, "isdisr", wcroot->wc_id,
                                                to_relpath,
                                                to_op_depth,
                                                repos_id,
                                                new_repos_relpath,
                                                revision));
      SVN_ERR(svn_sqlite__update(&affected, stmt));

#ifdef SVN_DEBUG
      /* Enable in release code?
         Broken moves are not fatal yet, but this assertion would break
         committing them */
      SVN_ERR_ASSERT(affected >= 1); /* If this fails there is no move dest */
#endif

      SVN_ERR(moved_descendant_collect(&map, wcroot, to_relpath, to_op_depth,
                                       iterpool, iterpool));
      SVN_ERR(moved_descendant_commit(wcroot, to_relpath,
                                      repos_id, new_repos_relpath, revision,
                                      map, iterpool));
    }

  svn_pool_destroy(iterpool);
  return SVN_NO_ERROR;
}