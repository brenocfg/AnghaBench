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
#define  IPI_CALL_FUNC 131 
#define  IPI_CALL_FUNC_SINGLE 130 
#define  IPI_RESCHEDULE 129 
#define  IPI_WAKEUP 128 
 int /*<<< orphan*/  WARN (int,char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  generic_smp_call_function_interrupt () ; 
 int /*<<< orphan*/  generic_smp_call_function_single_interrupt () ; 
 int /*<<< orphan*/  scheduler_ipi () ; 
 unsigned int smp_processor_id () ; 

void handle_IPI(unsigned int ipi_msg)
{
	unsigned int cpu = smp_processor_id();

	switch (ipi_msg) {
	case IPI_WAKEUP:
		break;

	case IPI_RESCHEDULE:
		scheduler_ipi();
		break;

	case IPI_CALL_FUNC:
		generic_smp_call_function_interrupt();
		break;

	case IPI_CALL_FUNC_SINGLE:
		generic_smp_call_function_single_interrupt();
		break;

	default:
		WARN(1, "CPU%u: Unknown IPI message 0x%x\n", cpu, ipi_msg);
		break;
	}
}