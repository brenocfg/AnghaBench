#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ number; int /*<<< orphan*/  change_set; } ;
struct TYPE_13__ {TYPE_5__* data_rep; TYPE_3__* prop_rep; TYPE_1__ noderev_id; } ;
typedef  TYPE_6__ svn_fs_x__noderev_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct TYPE_11__ {int /*<<< orphan*/  change_set; } ;
struct TYPE_12__ {TYPE_4__ id; } ;
struct TYPE_9__ {int /*<<< orphan*/  change_set; } ;
struct TYPE_10__ {TYPE_2__ id; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ SVN_FS_X__ITEM_INDEX_ROOT_NODE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ svn_fs_x__is_txn (int /*<<< orphan*/ ) ; 

svn_boolean_t
svn_fs_x__is_fresh_txn_root(svn_fs_x__noderev_t *noderev)
{
  /* Is it a root node? */
  if (noderev->noderev_id.number != SVN_FS_X__ITEM_INDEX_ROOT_NODE)
    return FALSE;

  /* ... in a transaction? */
  if (!svn_fs_x__is_txn(noderev->noderev_id.change_set))
    return FALSE;

  /* ... with no prop change in that txn?
     (Once we set a property, the prop rep will never become NULL again.) */
  if (noderev->prop_rep && svn_fs_x__is_txn(noderev->prop_rep->id.change_set))
    return FALSE;

  /* ... and no sub-tree change?
     (Once we set a text, the data rep will never become NULL again.) */
  if (noderev->data_rep && svn_fs_x__is_txn(noderev->data_rep->id.change_set))
    return FALSE;

  /* Root node of a txn with no changes. */
  return TRUE;
}