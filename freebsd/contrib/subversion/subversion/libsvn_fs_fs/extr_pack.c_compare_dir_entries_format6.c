#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ value; } ;
typedef  TYPE_1__ svn_sort__item_t ;
struct TYPE_8__ {scalar_t__ revision; scalar_t__ number; } ;
typedef  TYPE_2__ svn_fs_fs__id_part_t ;
struct TYPE_9__ {int /*<<< orphan*/  id; } ;
typedef  TYPE_3__ svn_fs_dirent_t ;

/* Variables and functions */
 TYPE_2__* svn_fs_fs__id_rev_item (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
compare_dir_entries_format6(const svn_sort__item_t *a,
                            const svn_sort__item_t *b)
{
  const svn_fs_dirent_t *lhs = (const svn_fs_dirent_t *) a->value;
  const svn_fs_dirent_t *rhs = (const svn_fs_dirent_t *) b->value;

  const svn_fs_fs__id_part_t *lhs_rev_item
    = svn_fs_fs__id_rev_item(lhs->id);
  const svn_fs_fs__id_part_t *rhs_rev_item
    = svn_fs_fs__id_rev_item(rhs->id);

  /* decreasing ("reverse") order on revs */
  if (lhs_rev_item->revision != rhs_rev_item->revision)
    return lhs_rev_item->revision > rhs_rev_item->revision ? -1 : 1;

  /* increasing order on offsets */
  if (lhs_rev_item->number != rhs_rev_item->number)
    return lhs_rev_item->number > rhs_rev_item->number ? 1 : -1;

  return 0;
}