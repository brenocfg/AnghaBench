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
typedef  int /*<<< orphan*/ * (* svn_cancel_func_t ) (void*) ;
struct svn_wc__db_info_t {scalar_t__ kind; scalar_t__ conflicted; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 char* apr_hash_this_key (int /*<<< orphan*/ *) ; 
 struct svn_wc__db_info_t* apr_hash_this_val (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * remove_node_conflict_markers (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ *) ; 
 char* svn_dirent_join (char const*,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_dir ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_wc__db_read_children_info (int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
remove_all_conflict_markers(svn_wc__db_t *db,
                            const char *src_dir_abspath,
                            const char *dst_dir_abspath,
                            svn_cancel_func_t cancel_func,
                            void *cancel_baton,
                            apr_pool_t *scratch_pool)
{
  apr_pool_t *iterpool = svn_pool_create(scratch_pool);
  apr_hash_t *nodes;
  apr_hash_t *conflicts; /* Unused */
  apr_hash_index_t *hi;

  /* Reuse a status helper to obtain all subdirs and conflicts in a single
     db transaction. */
  /* ### This uses a rifle to kill a fly. But at least it doesn't use heavy
          artillery. */
  SVN_ERR(svn_wc__db_read_children_info(&nodes, &conflicts, db,
                                        src_dir_abspath,
                                        FALSE /* base_tree_only */,
                                        scratch_pool, iterpool));

  for (hi = apr_hash_first(scratch_pool, nodes);
       hi;
       hi = apr_hash_next(hi))
    {
      const char *name = apr_hash_this_key(hi);
      struct svn_wc__db_info_t *info = apr_hash_this_val(hi);

      if (cancel_func)
        SVN_ERR(cancel_func(cancel_baton));

      if (info->conflicted)
        {
          svn_pool_clear(iterpool);
          SVN_ERR(remove_node_conflict_markers(
                            db,
                            svn_dirent_join(src_dir_abspath, name, iterpool),
                            svn_dirent_join(dst_dir_abspath, name, iterpool),
                            iterpool));
        }
      if (info->kind == svn_node_dir)
        {
          svn_pool_clear(iterpool);
          SVN_ERR(remove_all_conflict_markers(
                            db,
                            svn_dirent_join(src_dir_abspath, name, iterpool),
                            svn_dirent_join(dst_dir_abspath, name, iterpool),
                            cancel_func, cancel_baton,
                            iterpool));
        }
    }

  svn_pool_destroy(iterpool);
  return SVN_NO_ERROR;
}