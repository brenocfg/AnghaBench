#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int version_id; int num_counters; int bit_width; } ;
union cpuid10_eax {TYPE_1__ split; int /*<<< orphan*/  full; } ;
struct TYPE_6__ {int x86; int x86_model; } ;
struct TYPE_5__ {void* num_controls; void* num_counters; } ;

/* Variables and functions */
 int /*<<< orphan*/  OP_MAX_COUNTER ; 
 TYPE_3__ boot_cpu_data ; 
 int /*<<< orphan*/  cpuid_eax (int) ; 
 void* min (int,int /*<<< orphan*/ ) ; 
 void* num_counters ; 
 TYPE_2__ op_arch_perfmon_spec ; 

__attribute__((used)) static void arch_perfmon_setup_counters(void)
{
	union cpuid10_eax eax;

	eax.full = cpuid_eax(0xa);

	/* Workaround for BIOS bugs in 6/15. Taken from perfmon2 */
	if (eax.split.version_id == 0 && boot_cpu_data.x86 == 6 &&
	    boot_cpu_data.x86_model == 15) {
		eax.split.version_id = 2;
		eax.split.num_counters = 2;
		eax.split.bit_width = 40;
	}

	num_counters = min((int)eax.split.num_counters, OP_MAX_COUNTER);

	op_arch_perfmon_spec.num_counters = num_counters;
	op_arch_perfmon_spec.num_controls = num_counters;
}