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
struct trapframe {int dummy; } ;
struct intsrc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCPU_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apic_id ; 
 int /*<<< orphan*/  apic_idt_to_irq (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  intr_execute_handlers (struct intsrc*,struct trapframe*) ; 
 struct intsrc* intr_lookup_source (int /*<<< orphan*/ ) ; 

void
lapic_handle_intr(int vector, struct trapframe *frame)
{
	struct intsrc *isrc;

	isrc = intr_lookup_source(apic_idt_to_irq(PCPU_GET(apic_id),
	    vector));
	intr_execute_handlers(isrc, frame);
}