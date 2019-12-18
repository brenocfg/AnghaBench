#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_3__ {char* et_name; int et_flags; int et_quality; int et_frequency; int et_min_period; int et_max_period; int /*<<< orphan*/  et_start; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int ET_FLAGS_ONESHOT ; 
 int ET_FLAGS_PERCPU ; 
 int HYPERV_TIMER_FREQ ; 
 int et_register (TYPE_1__*) ; 
 int /*<<< orphan*/  smp_rendezvous (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__ vmbus_et ; 
 int /*<<< orphan*/  vmbus_et_config ; 
 int /*<<< orphan*/  vmbus_et_start ; 

__attribute__((used)) static int
vmbus_et_attach(device_t dev)
{
	/* TODO: use independent IDT vector */

	vmbus_et.et_name = "Hyper-V";
	vmbus_et.et_flags = ET_FLAGS_ONESHOT | ET_FLAGS_PERCPU;
	vmbus_et.et_quality = 1000;
	vmbus_et.et_frequency = HYPERV_TIMER_FREQ;
	vmbus_et.et_min_period = (0x00000001ULL << 32) / HYPERV_TIMER_FREQ;
	vmbus_et.et_max_period = (0xfffffffeULL << 32) / HYPERV_TIMER_FREQ;
	vmbus_et.et_start = vmbus_et_start;

	/*
	 * Delay a bit to make sure that hyperv_tc64 will not return 0,
	 * since writing 0 to STIMER0_COUNT will disable STIMER0.
	 */
	DELAY(100);
	smp_rendezvous(NULL, vmbus_et_config, NULL, NULL);

	return (et_register(&vmbus_et));
}