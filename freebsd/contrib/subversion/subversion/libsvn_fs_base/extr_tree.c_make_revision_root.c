#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
struct TYPE_5__ {int /*<<< orphan*/  rev; int /*<<< orphan*/  is_txn_root; TYPE_2__* fsap_data; } ;
typedef  TYPE_1__ svn_fs_root_t ;
typedef  int /*<<< orphan*/  dag_node_t ;
struct TYPE_6__ {int /*<<< orphan*/ * root_dir; } ;
typedef  TYPE_2__ base_root_data_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 TYPE_1__* make_root (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_fs_root_t *
make_revision_root(svn_fs_t *fs,
                   svn_revnum_t rev,
                   dag_node_t *root_dir,
                   apr_pool_t *pool)
{
  svn_fs_root_t *root = make_root(fs, pool);
  base_root_data_t *brd = root->fsap_data;

  root->is_txn_root = FALSE;
  root->rev = rev;
  brd->root_dir = root_dir;

  return root;
}