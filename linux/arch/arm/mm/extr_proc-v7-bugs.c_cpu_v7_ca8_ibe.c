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

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 scalar_t__ check_spectre_auxcr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_v7_spectre_init () ; 
 int /*<<< orphan*/  spectre_warned ; 
 int /*<<< orphan*/  this_cpu_ptr (int /*<<< orphan*/ *) ; 

void cpu_v7_ca8_ibe(void)
{
	if (check_spectre_auxcr(this_cpu_ptr(&spectre_warned), BIT(6)))
		cpu_v7_spectre_init();
}