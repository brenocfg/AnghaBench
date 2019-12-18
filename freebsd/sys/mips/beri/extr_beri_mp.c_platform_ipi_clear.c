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
 int /*<<< orphan*/  beripic_clear_ipi (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * picmap ; 
 int platform_processor_id () ; 

void
platform_ipi_clear(void)
{
	int cpuid;

	cpuid = platform_processor_id();

	beripic_clear_ipi(picmap[cpuid], cpuid);
}