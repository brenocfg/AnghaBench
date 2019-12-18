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
typedef  int u_int ;

/* Variables and functions */
 int /*<<< orphan*/  GSEL_APIC ; 
 int /*<<< orphan*/  IDTVEC (int /*<<< orphan*/ ) ; 
 int IDT_DTRACE_RET ; 
 int IDT_SYSCALL ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  SDT_APIC ; 
 int /*<<< orphan*/  SEL_KPL ; 
 int /*<<< orphan*/ ** ioint_handlers ; 
 scalar_t__ pti ; 
 int /*<<< orphan*/  rsvd ; 
 int /*<<< orphan*/  rsvd_pti ; 
 int /*<<< orphan*/  setidt (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
native_apic_disable_vector(u_int apic_id, u_int vector)
{

	KASSERT(vector != IDT_SYSCALL, ("Attempt to overwrite syscall entry"));
#ifdef KDTRACE_HOOKS
	KASSERT(vector != IDT_DTRACE_RET,
	    ("Attempt to overwrite DTrace entry"));
#endif
	KASSERT(ioint_handlers[vector / 32] != NULL,
	    ("No ISR handler for vector %u", vector));
#ifdef notyet
	/*
	 * We can not currently clear the idt entry because other cpus
	 * may have a valid vector at this offset.
	 */
	setidt(vector, pti ? &IDTVEC(rsvd_pti) : &IDTVEC(rsvd), SDT_APIC,
	    SEL_KPL, GSEL_APIC);
#endif
}