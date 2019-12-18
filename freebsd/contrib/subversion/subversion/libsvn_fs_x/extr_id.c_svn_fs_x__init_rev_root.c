#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_revnum_t ;
struct TYPE_3__ {int /*<<< orphan*/  number; int /*<<< orphan*/  change_set; } ;
typedef  TYPE_1__ svn_fs_x__id_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_FS_X__ITEM_INDEX_ROOT_NODE ; 
 int /*<<< orphan*/  svn_fs_x__change_set_by_rev (int /*<<< orphan*/ ) ; 

void
svn_fs_x__init_rev_root(svn_fs_x__id_t *noderev_id,
                        svn_revnum_t rev)
{
  noderev_id->change_set = svn_fs_x__change_set_by_rev(rev);
  noderev_id->number = SVN_FS_X__ITEM_INDEX_ROOT_NODE;
}