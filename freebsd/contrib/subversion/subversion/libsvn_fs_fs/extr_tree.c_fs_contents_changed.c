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
struct TYPE_5__ {scalar_t__ fs; } ;
typedef  TYPE_1__ svn_fs_root_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  dag_node_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_FS_GENERAL ; 
 int /*<<< orphan*/  SVN_ERR_FS_NOT_FILE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  get_dag (int /*<<< orphan*/ **,TYPE_1__*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ svn_fs_fs__dag_node_kind (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_fs_fs__dag_things_different (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_file ; 

__attribute__((used)) static svn_error_t *
fs_contents_changed(svn_boolean_t *changed_p,
                    svn_fs_root_t *root1,
                    const char *path1,
                    svn_fs_root_t *root2,
                    const char *path2,
                    svn_boolean_t strict,
                    apr_pool_t *pool)
{
  dag_node_t *node1, *node2;

  /* Check that roots are in the same fs. */
  if (root1->fs != root2->fs)
    return svn_error_create
      (SVN_ERR_FS_GENERAL, NULL,
       _("Cannot compare file contents between two different filesystems"));

  SVN_ERR(get_dag(&node1, root1, path1, pool));
  /* Make sure that path is file. */
  if (svn_fs_fs__dag_node_kind(node1) != svn_node_file)
    return svn_error_createf
      (SVN_ERR_FS_NOT_FILE, NULL, _("'%s' is not a file"), path1);

  SVN_ERR(get_dag(&node2, root2, path2, pool));
  /* Make sure that path is file. */
  if (svn_fs_fs__dag_node_kind(node2) != svn_node_file)
    return svn_error_createf
      (SVN_ERR_FS_NOT_FILE, NULL, _("'%s' is not a file"), path2);

  return svn_fs_fs__dag_things_different(NULL, changed_p,
                                         node1, node2, strict, pool);
}