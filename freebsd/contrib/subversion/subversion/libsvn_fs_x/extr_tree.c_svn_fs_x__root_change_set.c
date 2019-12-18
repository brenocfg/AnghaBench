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
typedef  int /*<<< orphan*/  svn_fs_x__change_set_t ;
struct TYPE_4__ {int /*<<< orphan*/  rev; scalar_t__ is_txn_root; } ;
typedef  TYPE_1__ svn_fs_root_t ;

/* Variables and functions */
 int /*<<< orphan*/  svn_fs_x__change_set_by_rev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_x__change_set_by_txn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_x__root_txn_id (TYPE_1__*) ; 

svn_fs_x__change_set_t
svn_fs_x__root_change_set(svn_fs_root_t *root)
{
  if (root->is_txn_root)
    return svn_fs_x__change_set_by_txn(svn_fs_x__root_txn_id(root));

  return svn_fs_x__change_set_by_rev(root->rev);
}