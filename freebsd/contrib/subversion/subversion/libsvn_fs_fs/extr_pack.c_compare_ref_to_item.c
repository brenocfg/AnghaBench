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
typedef  int /*<<< orphan*/  svn_fs_fs__id_part_t ;
struct TYPE_3__ {int /*<<< orphan*/  from; } ;
typedef  TYPE_1__ reference_t ;

/* Variables and functions */
 int svn_fs_fs__id_part_compare (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int
compare_ref_to_item(const reference_t * const * lhs_p,
                    const svn_fs_fs__id_part_t * rhs_p)
{
  return svn_fs_fs__id_part_compare(&(*lhs_p)->from, rhs_p);
}