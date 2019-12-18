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
 int PSL_DR ; 
 int PSL_SF ; 
 void* fdt ; 
 int mfmsr () ; 
 int* ofmsr ; 
 int ofw_real_mode ; 
 int /*<<< orphan*/  ofw_save_trap_vec (int /*<<< orphan*/ ) ; 
 int openfirmware_entry (void*) ; 
 int /*<<< orphan*/  save_trap_init ; 

void
OF_initial_setup(void *fdt_ptr, void *junk, int (*openfirm)(void *))
{
#ifdef AIM
	ofmsr[0] = mfmsr();
	#ifdef __powerpc64__
	ofmsr[0] &= ~PSL_SF;
	#else
	__asm __volatile("mfsprg0 %0" : "=&r"(ofmsr[1]));
	#endif
	__asm __volatile("mfsprg1 %0" : "=&r"(ofmsr[2]));
	__asm __volatile("mfsprg2 %0" : "=&r"(ofmsr[3]));
	__asm __volatile("mfsprg3 %0" : "=&r"(ofmsr[4]));
	openfirmware_entry = openfirm;

	if (ofmsr[0] & PSL_DR)
		ofw_real_mode = 0;
	else
		ofw_real_mode = 1;

	ofw_save_trap_vec(save_trap_init);
#else
	ofw_real_mode = 1;
#endif

	fdt = fdt_ptr;
}