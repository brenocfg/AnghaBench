#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  trail_t ;
struct TYPE_4__ {int /*<<< orphan*/  txn; int /*<<< orphan*/  fs; int /*<<< orphan*/  is_txn_root; TYPE_2__* fsap_data; } ;
typedef  TYPE_1__ svn_fs_root_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  dag_node_t ;
struct TYPE_5__ {int /*<<< orphan*/  root_dir; } ;
typedef  TYPE_2__ base_root_data_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * svn_fs_base__dag_dup (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_fs_base__dag_txn_root (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
root_node(dag_node_t **node_p,
          svn_fs_root_t *root,
          trail_t *trail,
          apr_pool_t *pool)
{
  base_root_data_t *brd = root->fsap_data;

  if (! root->is_txn_root)
    {
      /* It's a revision root, so we already have its root directory
         opened.  */
      *node_p = svn_fs_base__dag_dup(brd->root_dir, pool);
      return SVN_NO_ERROR;
    }
  else
    {
      /* It's a transaction root.  Open a fresh copy.  */
      return svn_fs_base__dag_txn_root(node_p, root->fs, root->txn,
                                       trail, pool);
    }
}