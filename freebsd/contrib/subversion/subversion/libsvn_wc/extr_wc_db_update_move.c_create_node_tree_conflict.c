#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  operation; int /*<<< orphan*/  new_version; TYPE_3__* old_version; int /*<<< orphan*/  db; int /*<<< orphan*/  dst_op_depth; int /*<<< orphan*/  wcroot; } ;
typedef  TYPE_1__ update_move_baton_t ;
typedef  int /*<<< orphan*/  svn_wc_conflict_reason_t ;
typedef  int /*<<< orphan*/  svn_wc_conflict_action_t ;
typedef  int /*<<< orphan*/  svn_skel_t ;
typedef  int /*<<< orphan*/  svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_6__ {char const* dst_relpath; TYPE_1__* umb; } ;
typedef  TYPE_2__ node_move_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_7__ {int /*<<< orphan*/  path_in_repos; } ;

/* Variables and functions */
 int /*<<< orphan*/  create_tree_conflict (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char const*,char*,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 char* svn_relpath_join (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* svn_relpath_prefix (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_relpath_skip_ancestor (char const*,char const*) ; 

__attribute__((used)) static svn_error_t *
create_node_tree_conflict(svn_skel_t **conflict_p,
                          node_move_baton_t *nmb,
                          const char *dst_local_relpath,
                          svn_node_kind_t old_kind,
                          svn_node_kind_t new_kind,
                          svn_wc_conflict_reason_t reason,
                          svn_wc_conflict_action_t action,
                          const char *move_src_op_root_relpath,
                          apr_pool_t *result_pool,
                          apr_pool_t *scratch_pool)
{
  update_move_baton_t *umb = nmb->umb;
  const char *dst_repos_relpath;
  const char *dst_root_relpath = svn_relpath_prefix(nmb->dst_relpath,
                                                    umb->dst_op_depth,
                                                    scratch_pool);

  dst_repos_relpath =
            svn_relpath_join(nmb->umb->old_version->path_in_repos,
                             svn_relpath_skip_ancestor(dst_root_relpath,
                                                       nmb->dst_relpath),
                             scratch_pool);

  return svn_error_trace(
            create_tree_conflict(conflict_p, umb->wcroot, dst_local_relpath,
                                 svn_relpath_prefix(dst_local_relpath,
                                                    umb->dst_op_depth,
                                                    scratch_pool),
                                 umb->db,
                                 umb->old_version, umb->new_version,
                                 umb->operation, old_kind, new_kind,
                                 dst_repos_relpath,
                                 reason, action, move_src_op_root_relpath,
                                 result_pool, scratch_pool));
}