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
 int /*<<< orphan*/  CVMX_CIU_MBOX_SETX (int) ; 
 int cpu_logical_map (int) ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,unsigned int) ; 

void octeon_send_ipi_single(int cpu, unsigned int action)
{
	int coreid = cpu_logical_map(cpu);
	/*
	pr_info("SMP: Mailbox send cpu=%d, coreid=%d, action=%u\n", cpu,
	       coreid, action);
	*/
	cvmx_write_csr(CVMX_CIU_MBOX_SETX(coreid), action);
}