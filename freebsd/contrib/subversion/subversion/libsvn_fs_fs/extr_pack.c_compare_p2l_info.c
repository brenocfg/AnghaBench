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
struct TYPE_5__ {scalar_t__ revision; scalar_t__ number; } ;
struct TYPE_6__ {TYPE_1__ item; } ;
typedef  TYPE_2__ svn_fs_fs__p2l_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static int
compare_p2l_info(const svn_fs_fs__p2l_entry_t * const * lhs,
                 const svn_fs_fs__p2l_entry_t * const * rhs)
{
  assert(*lhs != *rhs);

  if ((*lhs)->item.revision == (*rhs)->item.revision)
    return (*lhs)->item.number > (*rhs)->item.number ? -1 : 1;

  return (*lhs)->item.revision > (*rhs)->item.revision ? -1 : 1;
}