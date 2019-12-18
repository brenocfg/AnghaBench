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
struct TYPE_4__ {scalar_t__ change_set; } ;
typedef  TYPE_1__ svn_fs_x__id_t ;

/* Variables and functions */

__attribute__((used)) static int
compare_sub_items(const svn_fs_x__id_t * const * lhs,
                  const svn_fs_x__id_t * const * rhs)
{
  return (*lhs)->change_set < (*rhs)->change_set
       ? 1
       : ((*lhs)->change_set > (*rhs)->change_set ? -1 : 0);
}