#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ cpu_hyperthread; int /*<<< orphan*/  cpu_present; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* load ) (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 size_t* cpu_apic_ids ; 
 TYPE_2__* cpu_info ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ucode_data ; 
 TYPE_1__* ucode_loader ; 

void
ucode_load_ap(int cpu)
{
#ifdef SMP
	KASSERT(cpu_info[cpu_apic_ids[cpu]].cpu_present,
	    ("cpu %d not present", cpu));

	if (cpu_info[cpu_apic_ids[cpu]].cpu_hyperthread)
		return;
#endif

	if (ucode_data != NULL)
		(void)ucode_loader->load(ucode_data, false, NULL, NULL);
}