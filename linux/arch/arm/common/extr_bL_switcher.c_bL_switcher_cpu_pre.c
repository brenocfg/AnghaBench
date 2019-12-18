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
 int EINVAL ; 
 int /*<<< orphan*/  bL_switcher_active ; 
 int* bL_switcher_cpu_pairing ; 

__attribute__((used)) static int bL_switcher_cpu_pre(unsigned int cpu)
{
	int pairing;

	if (!bL_switcher_active)
		return 0;

	pairing = bL_switcher_cpu_pairing[cpu];

	if (pairing == -1)
		return -EINVAL;
	return 0;
}