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
typedef  int /*<<< orphan*/  u_int ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_CLR_ATOMIC (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CPU_ISSET (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PCPU_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpustop_handler () ; 
 int /*<<< orphan*/  ipi_stop_nmi_pending ; 

int
ipi_nmi_handler(void)
{
	u_int cpuid;

	/*
	 * As long as there is not a simple way to know about a NMI's
	 * source, if the bitmask for the current CPU is present in
	 * the global pending bitword an IPI_STOP_HARD has been issued
	 * and should be handled.
	 */
	cpuid = PCPU_GET(cpuid);
	if (!CPU_ISSET(cpuid, &ipi_stop_nmi_pending))
		return (1);

	CPU_CLR_ATOMIC(cpuid, &ipi_stop_nmi_pending);
	cpustop_handler();
	return (0);
}