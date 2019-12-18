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
struct ipi_data {int dummy; } ;

/* Variables and functions */
 unsigned long BITS_PER_LONG ; 
#define  IPI_CALL_FUNC 131 
#define  IPI_CPU_STOP 130 
#define  IPI_RESCHEDULE 129 
#define  IPI_TIMER 128 
 int /*<<< orphan*/  __vmstop () ; 
 unsigned long find_next_bit (unsigned long*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  generic_smp_call_function_interrupt () ; 
 int /*<<< orphan*/  ipi_timer () ; 
 int /*<<< orphan*/  scheduler_ipi () ; 

__attribute__((used)) static inline void __handle_ipi(unsigned long *ops, struct ipi_data *ipi,
				int cpu)
{
	unsigned long msg = 0;
	do {
		msg = find_next_bit(ops, BITS_PER_LONG, msg+1);

		switch (msg) {

		case IPI_TIMER:
			ipi_timer();
			break;

		case IPI_CALL_FUNC:
			generic_smp_call_function_interrupt();
			break;

		case IPI_CPU_STOP:
			/*
			 * call vmstop()
			 */
			__vmstop();
			break;

		case IPI_RESCHEDULE:
			scheduler_ipi();
			break;
		}
	} while (msg < BITS_PER_LONG);
}