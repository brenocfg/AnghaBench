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
typedef  scalar_t__ svn_revnum_t ;
struct TYPE_4__ {TYPE_1__* loc1; } ;
typedef  TYPE_2__ merge_source_t ;
struct TYPE_3__ {scalar_t__ rev; } ;

/* Variables and functions */

__attribute__((used)) static int
compare_merge_source_ts(const void *a,
                        const void *b)
{
  svn_revnum_t a_rev = (*(const merge_source_t *const *)a)->loc1->rev;
  svn_revnum_t b_rev = (*(const merge_source_t *const *)b)->loc1->rev;
  if (a_rev == b_rev)
    return 0;
  return a_rev < b_rev ? 1 : -1;
}