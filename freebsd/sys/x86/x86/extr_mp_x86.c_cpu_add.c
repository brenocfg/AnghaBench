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
typedef  size_t u_int ;
struct TYPE_2__ {int cpu_present; int cpu_bsp; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int boot_cpu_id ; 
 scalar_t__ bootverbose ; 
 TYPE_1__* cpu_info ; 
 size_t max_apic_id ; 
 int /*<<< orphan*/  panic (char*,size_t) ; 
 int /*<<< orphan*/  printf (char*,size_t,char*) ; 

void
cpu_add(u_int apic_id, char boot_cpu)
{

	if (apic_id > max_apic_id) {
		panic("SMP: APIC ID %d too high", apic_id);
		return;
	}
	KASSERT(cpu_info[apic_id].cpu_present == 0, ("CPU %u added twice",
	    apic_id));
	cpu_info[apic_id].cpu_present = 1;
	if (boot_cpu) {
		KASSERT(boot_cpu_id == -1,
		    ("CPU %u claims to be BSP, but CPU %u already is", apic_id,
		    boot_cpu_id));
		boot_cpu_id = apic_id;
		cpu_info[apic_id].cpu_bsp = 1;
	}
	if (bootverbose)
		printf("SMP: Added CPU %u (%s)\n", apic_id, boot_cpu ? "BSP" :
		    "AP");
}