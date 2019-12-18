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
struct TYPE_4__ {int /*<<< orphan*/ * fsap_data; int /*<<< orphan*/  is_txn_root; } ;
typedef  TYPE_1__ svn_fs_root_t ;
typedef  int /*<<< orphan*/  svn_fs_id_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  dag_node_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  get_dag (int /*<<< orphan*/ **,TYPE_1__*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__dag_get_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_fs_fs__id_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_fs__node_id(const svn_fs_id_t **id_p,
                   svn_fs_root_t *root,
                   const char *path,
                   apr_pool_t *pool)
{
  if ((! root->is_txn_root)
      && (path[0] == '\0' || ((path[0] == '/') && (path[1] == '\0'))))
    {
      /* Optimize the case where we don't need any db access at all.
         The root directory ("" or "/") node is stored in the
         svn_fs_root_t object, and never changes when it's a revision
         root, so we can just reach in and grab it directly. */
      dag_node_t *root_dir = root->fsap_data;
      *id_p = svn_fs_fs__id_copy(svn_fs_fs__dag_get_id(root_dir), pool);
    }
  else
    {
      dag_node_t *node;

      SVN_ERR(get_dag(&node, root, path, pool));
      *id_p = svn_fs_fs__id_copy(svn_fs_fs__dag_get_id(node), pool);
    }
  return SVN_NO_ERROR;
}