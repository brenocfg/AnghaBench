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
typedef  int /*<<< orphan*/  svn_fs_root_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  dag_node_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  get_dag (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__dag_get_copyfrom_path (char const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__dag_get_copyfrom_rev (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
fs_copied_from(svn_revnum_t *rev_p,
               const char **path_p,
               svn_fs_root_t *root,
               const char *path,
               apr_pool_t *pool)
{
  dag_node_t *node;

  /* There is no cached entry, look it up the old-fashioned
      way. */
  SVN_ERR(get_dag(&node, root, path, pool));
  SVN_ERR(svn_fs_fs__dag_get_copyfrom_rev(rev_p, node));
  SVN_ERR(svn_fs_fs__dag_get_copyfrom_path(path_p, node));

  return SVN_NO_ERROR;
}