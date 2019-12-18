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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 unsigned long __prepare_ICR (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  native_x2apic_icr_write (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  x2apic_wrmsr_fence () ; 

void __x2apic_send_IPI_shorthand(int vector, u32 which)
{
	unsigned long cfg = __prepare_ICR(which, vector, 0);

	x2apic_wrmsr_fence();
	native_x2apic_icr_write(cfg, 0);
}