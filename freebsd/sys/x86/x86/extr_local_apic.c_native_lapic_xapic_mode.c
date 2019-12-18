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
typedef  int /*<<< orphan*/  register_t ;

/* Variables and functions */
 int /*<<< orphan*/  intr_disable () ; 
 int /*<<< orphan*/  intr_restore (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  native_lapic_enable_x2apic () ; 
 scalar_t__ x2apic_mode ; 

__attribute__((used)) static void
native_lapic_xapic_mode(void)
{
	register_t saveintr;

	saveintr = intr_disable();
	if (x2apic_mode)
		native_lapic_enable_x2apic();
	intr_restore(saveintr);
}