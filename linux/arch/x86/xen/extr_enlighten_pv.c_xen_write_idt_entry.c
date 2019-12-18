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
struct trap_info {scalar_t__ address; } ;
typedef  int /*<<< orphan*/  gate_desc ;
struct TYPE_2__ {int /*<<< orphan*/  size; int /*<<< orphan*/  address; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 scalar_t__ HYPERVISOR_set_trap_table (struct trap_info*) ; 
 unsigned long __this_cpu_read (int /*<<< orphan*/ ) ; 
 scalar_t__ cvt_gate_to_trap (int,int /*<<< orphan*/  const*,struct trap_info*) ; 
 TYPE_1__ idt_desc ; 
 int /*<<< orphan*/  native_write_idt_entry (int /*<<< orphan*/ *,int,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int /*<<< orphan*/  trace_xen_cpu_write_idt_entry (int /*<<< orphan*/ *,int,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  xen_mc_flush () ; 

__attribute__((used)) static void xen_write_idt_entry(gate_desc *dt, int entrynum, const gate_desc *g)
{
	unsigned long p = (unsigned long)&dt[entrynum];
	unsigned long start, end;

	trace_xen_cpu_write_idt_entry(dt, entrynum, g);

	preempt_disable();

	start = __this_cpu_read(idt_desc.address);
	end = start + __this_cpu_read(idt_desc.size) + 1;

	xen_mc_flush();

	native_write_idt_entry(dt, entrynum, g);

	if (p >= start && (p + 8) <= end) {
		struct trap_info info[2];

		info[1].address = 0;

		if (cvt_gate_to_trap(entrynum, g, &info[0]))
			if (HYPERVISOR_set_trap_table(info))
				BUG();
	}

	preempt_enable();
}