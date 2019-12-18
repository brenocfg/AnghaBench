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
struct IO_APIC_route_entry {int dummy; } ;
struct TYPE_2__ {int nr_registers; scalar_t__ saved_registers; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 TYPE_1__* ioapics ; 
 scalar_t__ kzalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 

__attribute__((used)) static void alloc_ioapic_saved_registers(int idx)
{
	size_t size;

	if (ioapics[idx].saved_registers)
		return;

	size = sizeof(struct IO_APIC_route_entry) * ioapics[idx].nr_registers;
	ioapics[idx].saved_registers = kzalloc(size, GFP_KERNEL);
	if (!ioapics[idx].saved_registers)
		pr_err("IOAPIC %d: suspend/resume impossible!\n", idx);
}