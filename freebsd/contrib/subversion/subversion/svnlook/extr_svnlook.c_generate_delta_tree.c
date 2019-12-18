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
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_repos_t ;
typedef  int /*<<< orphan*/  svn_repos_node_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_fs_root_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_delta_editor_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  svn_fs_revision_root (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_repos_fs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_repos_node_editor (int /*<<< orphan*/  const**,void**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_repos_node_from_baton (void*) ; 
 int /*<<< orphan*/  svn_repos_replay2 (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
generate_delta_tree(svn_repos_node_t **tree,
                    svn_repos_t *repos,
                    svn_fs_root_t *root,
                    svn_revnum_t base_rev,
                    apr_pool_t *pool)
{
  svn_fs_root_t *base_root;
  const svn_delta_editor_t *editor;
  void *edit_baton;
  apr_pool_t *edit_pool = svn_pool_create(pool);
  svn_fs_t *fs = svn_repos_fs(repos);

  /* Get the base root. */
  SVN_ERR(svn_fs_revision_root(&base_root, fs, base_rev, pool));

  /* Request our editor. */
  SVN_ERR(svn_repos_node_editor(&editor, &edit_baton, repos,
                                base_root, root, pool, edit_pool));

  /* Drive our editor. */
  SVN_ERR(svn_repos_replay2(root, "", SVN_INVALID_REVNUM, TRUE,
                            editor, edit_baton, NULL, NULL, edit_pool));

  /* Return the tree we just built. */
  *tree = svn_repos_node_from_baton(edit_baton);
  svn_pool_destroy(edit_pool);
  return SVN_NO_ERROR;
}