#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  change_set; int /*<<< orphan*/  number; } ;
struct TYPE_10__ {TYPE_1__* data_rep; TYPE_3__ noderev_id; } ;
typedef  TYPE_2__ svn_fs_x__noderev_t ;
typedef  TYPE_3__ svn_fs_x__id_t ;
struct TYPE_12__ {int /*<<< orphan*/ * dir_cache; } ;
typedef  TYPE_4__ svn_fs_x__data_t ;
struct TYPE_13__ {TYPE_4__* fsap_data; } ;
typedef  TYPE_5__ svn_fs_t ;
typedef  int /*<<< orphan*/  svn_cache__t ;
struct TYPE_9__ {TYPE_3__ id; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_FS_X__INVALID_CHANGE_SET ; 
 int /*<<< orphan*/  SVN_FS_X__ITEM_INDEX_UNUSED ; 
 scalar_t__ svn_fs_x__is_txn (int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_cache__t *
locate_dir_cache(svn_fs_t *fs,
                 svn_fs_x__id_t *key,
                 svn_fs_x__noderev_t *noderev)
{
  svn_fs_x__data_t *ffd = fs->fsap_data;

  if (!noderev->data_rep)
    {
      /* no data rep -> empty directory.
         Use a key that does definitely not clash with non-NULL reps. */
      key->change_set = SVN_FS_X__INVALID_CHANGE_SET;
      key->number = SVN_FS_X__ITEM_INDEX_UNUSED;
    }
  else if (svn_fs_x__is_txn(noderev->noderev_id.change_set))
    {
      /* data in txns must be addressed by noderev ID since the
         representation has not been created, yet. */
      *key = noderev->noderev_id;
    }
  else
    {
      /* committed data can use simple rev,item pairs */
      *key = noderev->data_rep->id;
    }

  return ffd->dir_cache;
}