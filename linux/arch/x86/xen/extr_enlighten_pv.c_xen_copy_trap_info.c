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
struct trap_info {int dummy; } ;
struct desc_ptr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  idt_desc ; 
 struct desc_ptr* this_cpu_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xen_convert_trap_info (struct desc_ptr const*,struct trap_info*) ; 

void xen_copy_trap_info(struct trap_info *traps)
{
	const struct desc_ptr *desc = this_cpu_ptr(&idt_desc);

	xen_convert_trap_info(desc, traps);
}