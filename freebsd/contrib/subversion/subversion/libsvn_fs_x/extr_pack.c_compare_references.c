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
struct TYPE_4__ {int /*<<< orphan*/  from; int /*<<< orphan*/  to; } ;
typedef  TYPE_1__ reference_t ;

/* Variables and functions */
 int svn_fs_x__id_compare (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
compare_references(const reference_t * const * lhs_p,
                   const reference_t * const * rhs_p)
{
  const reference_t * lhs = *lhs_p;
  const reference_t * rhs = *rhs_p;

  int diff = svn_fs_x__id_compare(&lhs->to, &rhs->to);
  return diff ? diff : svn_fs_x__id_compare(&lhs->from, &rhs->from);
}