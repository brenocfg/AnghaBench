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
struct dmar_unit {int hw_cap; } ;

/* Variables and functions */

__attribute__((used)) static void
cpu_e5_am9(struct dmar_unit *unit)
{

	unit->hw_cap &= ~(0x3fULL << 48);
	unit->hw_cap |= (9ULL << 48);
}