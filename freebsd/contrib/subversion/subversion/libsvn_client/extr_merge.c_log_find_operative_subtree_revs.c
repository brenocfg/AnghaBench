#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ svn_node_kind_t ;
struct TYPE_6__ {int /*<<< orphan*/  changed_paths2; } ;
typedef  TYPE_1__ svn_log_entry_t ;
struct TYPE_7__ {scalar_t__ node_kind; char action; } ;
typedef  TYPE_2__ svn_log_changed_path2_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_8__ {scalar_t__ depth; int /*<<< orphan*/  result_pool; int /*<<< orphan*/  operative_children; int /*<<< orphan*/  merge_target_abspath; int /*<<< orphan*/  wc_ctx; int /*<<< orphan*/  merge_source_fspath; } ;
typedef  TYPE_3__ log_find_operative_subtree_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 char* apr_hash_this_key (int /*<<< orphan*/ *) ; 
 TYPE_2__* apr_hash_this_val (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_pstrdup (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ svn_depth_files ; 
 scalar_t__ svn_depth_immediates ; 
 char* svn_dirent_join (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 char* svn_fspath__skip_ancestor (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  svn_hash_gets (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ svn_node_dir ; 
 scalar_t__ svn_node_unknown ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 char* svn_relpath_dirname (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_read_kind2 (scalar_t__*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
log_find_operative_subtree_revs(void *baton,
                                svn_log_entry_t *log_entry,
                                apr_pool_t *pool)
{
  log_find_operative_subtree_baton_t *log_baton = baton;
  apr_hash_index_t *hi;
  apr_pool_t *iterpool;

  /* It's possible that authz restrictions on the merge source prevent us
     from knowing about any of the changes for LOG_ENTRY->REVISION. */
  if (!log_entry->changed_paths2)
    return SVN_NO_ERROR;

  iterpool = svn_pool_create(pool);

  for (hi = apr_hash_first(pool, log_entry->changed_paths2);
       hi;
       hi = apr_hash_next(hi))
    {
      const char *path = apr_hash_this_key(hi);
      svn_log_changed_path2_t *change = apr_hash_this_val(hi);

        {
          const char *child;
          const char *potential_child;
          const char *rel_path =
            svn_fspath__skip_ancestor(log_baton->merge_source_fspath, path);

          /* Some affected paths might be the root of the merge source or
             entirely outside our subtree of interest. In either case they
             are not operative *immediate* children. */
          if (rel_path == NULL
              || rel_path[0] == '\0')
            continue;

          svn_pool_clear(iterpool);

          child = svn_relpath_dirname(rel_path, iterpool);
          if (child[0] == '\0')
            {
              /* The svn_log_changed_path2_t.node_kind members in
                 LOG_ENTRY->CHANGED_PATHS2 may be set to
                 svn_node_unknown, see svn_log_changed_path2_t and
                 svn_fs_paths_changed2.  In that case we check the
                 type of the corresponding subtree in the merge
                 target. */
              svn_node_kind_t node_kind;

              if (change->node_kind == svn_node_unknown)
                {
                  const char *wc_child_abspath =
                    svn_dirent_join(log_baton->merge_target_abspath,
                                    rel_path, iterpool);

                  SVN_ERR(svn_wc_read_kind2(&node_kind, log_baton->wc_ctx,
                                            wc_child_abspath, FALSE, FALSE,
                                            iterpool));
                }
              else
                {
                  node_kind = change->node_kind;
                }

              /* We only care about immediate directory children if
                 DEPTH is svn_depth_files. */
              if (log_baton->depth == svn_depth_files
                  && node_kind != svn_node_dir)
                continue;

              /* If depth is svn_depth_immediates, then we only care
                 about changes to proper subtrees of PATH.  If the change
                 is to PATH itself then PATH is within the operational
                 depth of the merge. */
              if (log_baton->depth == svn_depth_immediates)
                continue;

              child = rel_path;
            }

          potential_child = svn_dirent_join(log_baton->merge_target_abspath,
                                            child, iterpool);

          if (change->action == 'A'
              || !svn_hash_gets(log_baton->operative_children,
                                potential_child))
            {
              svn_hash_sets(log_baton->operative_children,
                            apr_pstrdup(log_baton->result_pool,
                                        potential_child),
                            apr_pstrdup(log_baton->result_pool, path));
            }
        }
    }
  svn_pool_destroy(iterpool);
  return SVN_NO_ERROR;
}