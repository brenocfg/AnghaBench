#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  ec_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  ec_call_function_single ; 
 int /*<<< orphan*/  ec_schedule ; 
 int /*<<< orphan*/  ec_stop_cpu ; 
 int /*<<< orphan*/  generic_smp_call_function_single_interrupt () ; 
 TYPE_1__* pcpu_devices ; 
 int /*<<< orphan*/  scheduler_ipi () ; 
 size_t smp_processor_id () ; 
 int /*<<< orphan*/  smp_stop_cpu () ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,unsigned long*) ; 
 unsigned long xchg (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void smp_handle_ext_call(void)
{
	unsigned long bits;

	/* handle bit signal external calls */
	bits = xchg(&pcpu_devices[smp_processor_id()].ec_mask, 0);
	if (test_bit(ec_stop_cpu, &bits))
		smp_stop_cpu();
	if (test_bit(ec_schedule, &bits))
		scheduler_ipi();
	if (test_bit(ec_call_function_single, &bits))
		generic_smp_call_function_single_interrupt();
}