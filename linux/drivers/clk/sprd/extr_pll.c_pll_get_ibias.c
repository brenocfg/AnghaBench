#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ const u64 ;
typedef  int u32 ;

/* Variables and functions */

__attribute__((used)) static u32 pll_get_ibias(u64 rate, const u64 *table)
{
	u32 i, num = table[0];

	for (i = 1; i < num + 1; i++)
		if (rate <= table[i])
			break;

	return (i == num + 1) ? num : i;
}