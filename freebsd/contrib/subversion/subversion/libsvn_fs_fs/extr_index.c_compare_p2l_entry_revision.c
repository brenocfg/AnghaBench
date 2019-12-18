#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ revision; } ;
struct TYPE_4__ {TYPE_1__ item; } ;
typedef  TYPE_2__ svn_fs_fs__p2l_entry_t ;

/* Variables and functions */

__attribute__((used)) static int
compare_p2l_entry_revision(const void *lhs,
                           const void *rhs)
{
  const svn_fs_fs__p2l_entry_t *lhs_entry
    =*(const svn_fs_fs__p2l_entry_t **)lhs;
  const svn_fs_fs__p2l_entry_t *rhs_entry
    =*(const svn_fs_fs__p2l_entry_t **)rhs;

  if (lhs_entry->item.revision < rhs_entry->item.revision)
    return -1;

  return lhs_entry->item.revision == rhs_entry->item.revision ? 0 : 1;
}