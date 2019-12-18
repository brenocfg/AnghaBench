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

/* Variables and functions */
 int PSL_EE ; 
 int /*<<< orphan*/  cninit_finish () ; 
 scalar_t__ cold ; 
 int mfmsr () ; 
 int /*<<< orphan*/  mtmsr (int) ; 
 int /*<<< orphan*/  powerpc_enable_intr () ; 

__attribute__((used)) static void
configure_final(void *dummy)
{

	/*
	 * Now that we're guaranteed to have a PIC driver (or we'll never
	 * have one), program it with all the previously setup interrupts.
	 */
	powerpc_enable_intr();

	/* Enable external interrupts. */
	mtmsr(mfmsr() | PSL_EE);

	cninit_finish();
	cold = 0;
}