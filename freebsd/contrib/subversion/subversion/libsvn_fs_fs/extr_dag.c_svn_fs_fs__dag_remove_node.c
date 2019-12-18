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
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_fs_id_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  dag_node_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_FS_NOT_MUTABLE ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  svn_fs_fs__dag_check_mutable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__dag_get_node (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_fs_fs__delete_node_revision (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_fs__dag_remove_node(svn_fs_t *fs,
                           const svn_fs_id_t *id,
                           apr_pool_t *pool)
{
  dag_node_t *node;

  /* Fetch the node. */
  SVN_ERR(svn_fs_fs__dag_get_node(&node, fs, id, pool));

  /* If immutable, do nothing and return immediately. */
  if (! svn_fs_fs__dag_check_mutable(node))
    return svn_error_createf(SVN_ERR_FS_NOT_MUTABLE, NULL,
                             "Attempted removal of immutable node");

  /* Delete the node revision. */
  return svn_fs_fs__delete_node_revision(fs, id, pool);
}