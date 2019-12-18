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
 int hard_smp_processor_id () ; 
 int /*<<< orphan*/  opal_int_set_mfrr (int,int) ; 

__attribute__((used)) static void icp_opal_teardown_cpu(void)
{
	int hw_cpu = hard_smp_processor_id();

	/* Clear any pending IPI */
	opal_int_set_mfrr(hw_cpu, 0xff);
}