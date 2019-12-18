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
struct TYPE_4__ {int /*<<< orphan*/  abspath; int /*<<< orphan*/  wc_id; int /*<<< orphan*/  sdb; } ;
typedef  TYPE_1__ svn_wc__db_wcroot_t ;
typedef  int /*<<< orphan*/  svn_sqlite__stmt_t ;
typedef  scalar_t__ svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_depth_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;

/* Variables and functions */
 int /*<<< orphan*/  STMT_SELECT_IPROPS_CHILDREN ; 
 int /*<<< orphan*/  STMT_SELECT_IPROPS_NODE ; 
 int /*<<< orphan*/  STMT_SELECT_IPROPS_RECURSIVE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 char* apr_hash_this_key (int /*<<< orphan*/ *) ; 
 scalar_t__ svn_depth_empty ; 
 scalar_t__ svn_depth_files ; 
 scalar_t__ svn_depth_immediates ; 
 char* svn_dirent_is_child (char const*,char const*,int /*<<< orphan*/ *) ; 
 char* svn_dirent_join (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ *,char const*,char*) ; 
 scalar_t__ svn_node_file ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__bindf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char const*) ; 
 char* svn_sqlite__column_text (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__get_statement (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_sqlite__reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__step (scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_base_get_info_internal (int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
get_children_with_cached_iprops(apr_hash_t **iprop_paths,
                                svn_wc__db_wcroot_t *wcroot,
                                const char *local_relpath,
                                svn_depth_t depth,
                                apr_pool_t *result_pool,
                                apr_pool_t *scratch_pool)
{
  svn_sqlite__stmt_t *stmt;
  svn_boolean_t have_row;

  *iprop_paths = apr_hash_make(result_pool);

  /* First check if LOCAL_RELPATH itself has iprops */
  SVN_ERR(svn_sqlite__get_statement(&stmt, wcroot->sdb,
                                    STMT_SELECT_IPROPS_NODE));
  SVN_ERR(svn_sqlite__bindf(stmt, "is", wcroot->wc_id, local_relpath));
  SVN_ERR(svn_sqlite__step(&have_row, stmt));

  if (have_row)
   {
      const char *relpath_with_cache = svn_sqlite__column_text(stmt, 0,
                                                               NULL);
      const char *abspath_with_cache = svn_dirent_join(wcroot->abspath,
                                                       relpath_with_cache,
                                                       result_pool);
      svn_hash_sets(*iprop_paths, abspath_with_cache,
                    svn_sqlite__column_text(stmt, 1, result_pool));
    }
  SVN_ERR(svn_sqlite__reset(stmt));

  if (depth == svn_depth_empty)
    return SVN_NO_ERROR;

  /* Now fetch information for children or all descendants */
  if (depth == svn_depth_files
      || depth == svn_depth_immediates)
    {
      SVN_ERR(svn_sqlite__get_statement(&stmt, wcroot->sdb,
                                        STMT_SELECT_IPROPS_CHILDREN));
    }
  else /* Default to svn_depth_infinity. */
    {
      SVN_ERR(svn_sqlite__get_statement(&stmt, wcroot->sdb,
                                        STMT_SELECT_IPROPS_RECURSIVE));
    }

  SVN_ERR(svn_sqlite__bindf(stmt, "is", wcroot->wc_id, local_relpath));
  SVN_ERR(svn_sqlite__step(&have_row, stmt));

  while (have_row)
    {
      const char *relpath_with_cache = svn_sqlite__column_text(stmt, 0,
                                                               NULL);
      const char *abspath_with_cache = svn_dirent_join(wcroot->abspath,
                                                       relpath_with_cache,
                                                       result_pool);
      svn_hash_sets(*iprop_paths, abspath_with_cache,
                    svn_sqlite__column_text(stmt, 1, result_pool));
      SVN_ERR(svn_sqlite__step(&have_row, stmt));
    }

  SVN_ERR(svn_sqlite__reset(stmt));

  /* For depth files we should filter non files */
  if (depth == svn_depth_files)
    {
      apr_hash_index_t *hi;
      apr_pool_t *iterpool = svn_pool_create(scratch_pool);

      for (hi = apr_hash_first(scratch_pool, *iprop_paths);
           hi;
           hi = apr_hash_next(hi))
        {
          const char *child_abspath = apr_hash_this_key(hi);
          const char *child_relpath;
          svn_node_kind_t child_kind;

          svn_pool_clear(iterpool);

          child_relpath = svn_dirent_is_child(local_relpath, child_abspath,
                                              NULL);

          if (! child_relpath)
            {
              continue; /* local_relpath itself */
            }

          SVN_ERR(svn_wc__db_base_get_info_internal(NULL, &child_kind, NULL,
                                                    NULL, NULL, NULL, NULL,
                                                    NULL, NULL, NULL, NULL,
                                                    NULL, NULL, NULL, NULL,
                                                    wcroot, child_relpath,
                                                    scratch_pool,
                                                    scratch_pool));

          /* Filter if not a file */
          if (child_kind != svn_node_file)
            {
              svn_hash_sets(*iprop_paths, child_abspath, NULL);
            }
        }

      svn_pool_destroy(iterpool);
    }

  return SVN_NO_ERROR;
}