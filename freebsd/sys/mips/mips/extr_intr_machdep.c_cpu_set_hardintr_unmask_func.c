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
typedef  int /*<<< orphan*/  cpu_intr_unmask_t ;

/* Variables and functions */
 int /*<<< orphan*/  hardintr_unmask_func ; 

void
cpu_set_hardintr_unmask_func(cpu_intr_unmask_t func)
{

	hardintr_unmask_func = func;
}