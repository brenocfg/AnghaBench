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
struct TYPE_6__ {scalar_t__ item_count; TYPE_1__* items; } ;
typedef  TYPE_2__ svn_fs_x__p2l_entry_t ;
struct TYPE_5__ {scalar_t__ change_set; scalar_t__ number; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static int
compare_p2l_info(const svn_fs_x__p2l_entry_t * const * lhs,
                 const svn_fs_x__p2l_entry_t * const * rhs)
{
  assert(*lhs != *rhs);
  if ((*lhs)->item_count == 0)
    return (*lhs)->item_count == 0 ? 0 : -1;
  if ((*lhs)->item_count == 0)
    return 1;

  if ((*lhs)->items[0].change_set == (*rhs)->items[0].change_set)
    return (*lhs)->items[0].number > (*rhs)->items[0].number ? -1 : 1;

  return (*lhs)->items[0].change_set > (*rhs)->items[0].change_set ? -1 : 1;
}