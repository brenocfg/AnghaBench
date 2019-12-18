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
 int /*<<< orphan*/  icp_native_set_qirr (int,int) ; 
 int smp_processor_id () ; 

__attribute__((used)) static void icp_native_teardown_cpu(void)
{
	int cpu = smp_processor_id();

	/* Clear any pending IPI */
	icp_native_set_qirr(cpu, 0xff);
}