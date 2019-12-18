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
struct TYPE_4__ {int /*<<< orphan*/ * fsap_data; int /*<<< orphan*/  fs; scalar_t__ is_txn_root; } ;
typedef  TYPE_1__ svn_fs_root_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  dag_node_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  root_txn_id (TYPE_1__*) ; 
 int /*<<< orphan*/ * svn_fs_fs__dag_dup (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_fs_fs__dag_txn_root (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
root_node(dag_node_t **node_p,
          svn_fs_root_t *root,
          apr_pool_t *pool)
{
  if (root->is_txn_root)
    {
      /* It's a transaction root.  Open a fresh copy.  */
      return svn_fs_fs__dag_txn_root(node_p, root->fs, root_txn_id(root),
                                     pool);
    }
  else
    {
      /* It's a revision root, so we already have its root directory
         opened.  */
      dag_node_t *root_dir = root->fsap_data;
      *node_p = svn_fs_fs__dag_dup(root_dir, pool);
      return SVN_NO_ERROR;
    }
}