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
typedef  int u32 ;
struct TYPE_2__ {int socket_id; } ;

/* Variables and functions */
 TYPE_1__* cpu_data (int) ; 

void arch_fix_phys_package_id(int num, u32 slot)
{
#ifdef CONFIG_SMP
	if (cpu_data(num)->socket_id == -1)
		cpu_data(num)->socket_id = slot;
#endif
}