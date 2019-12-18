#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct TYPE_2__ {scalar_t__ val; } ;
typedef  TYPE_1__ hcstat_table_t ;

/* Variables and functions */

__attribute__((used)) static int sp_comp_val (const void *p1, const void *p2)
{
  const hcstat_table_t *b1 = (const hcstat_table_t *) p1;
  const hcstat_table_t *b2 = (const hcstat_table_t *) p2;

  const u64 v1 = b1->val;
  const u64 v2 = b2->val;

  if (v1 < v2) return  1;
  if (v1 > v2) return -1;

  return 0;
}