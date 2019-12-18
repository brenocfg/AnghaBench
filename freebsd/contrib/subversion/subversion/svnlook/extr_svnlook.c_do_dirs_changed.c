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
struct TYPE_5__ {int /*<<< orphan*/  repos; } ;
typedef  TYPE_1__ svnlook_ctxt_t ;
typedef  scalar_t__ svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_repos_node_t ;
typedef  int /*<<< orphan*/  svn_fs_root_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  generate_delta_tree (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_base_rev (scalar_t__*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_root (int /*<<< orphan*/ **,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_dirs_changed_tree (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
do_dirs_changed(svnlook_ctxt_t *c, apr_pool_t *pool)
{
  svn_fs_root_t *root;
  svn_revnum_t base_rev_id;
  svn_repos_node_t *tree;

  SVN_ERR(get_root(&root, c, pool));
  SVN_ERR(get_base_rev(&base_rev_id, c, pool));
  if (base_rev_id == SVN_INVALID_REVNUM)
    return SVN_NO_ERROR;

  SVN_ERR(generate_delta_tree(&tree, c->repos, root, base_rev_id, pool));
  if (tree)
    SVN_ERR(print_dirs_changed_tree(tree, "", pool));

  return SVN_NO_ERROR;
}