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
typedef  uintptr_t vm_offset_t ;
typedef  uintptr_t u_long ;

/* Variables and functions */
#define  FSL_E500mc 130 
#define  FSL_E5500 129 
#define  FSL_E6500 128 
 scalar_t__ __bss_start ; 
 uintptr_t __endkernel ; 
 scalar_t__ __sbss_end ; 
 scalar_t__ __sbss_start ; 
 scalar_t__ _end ; 
 scalar_t__ booke_check_for_fdt (uintptr_t,uintptr_t*) ; 
 int /*<<< orphan*/  booke_enable_bpred () ; 
 int /*<<< orphan*/  booke_enable_l1_cache () ; 
 int /*<<< orphan*/  booke_enable_l2_cache () ; 
 int /*<<< orphan*/ * bootinfo ; 
 int /*<<< orphan*/  bzero (scalar_t__,scalar_t__) ; 
 int cacheline_size ; 
 scalar_t__ fdt_totalsize (void*) ; 
 scalar_t__ kernload ; 
 int /*<<< orphan*/  memmove (void*,void*,scalar_t__) ; 
 int mfpvr () ; 
 uintptr_t powerpc_init (uintptr_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int) ; 
 uintptr_t roundup (uintptr_t,int) ; 
 int /*<<< orphan*/  tlb1_init () ; 

uintptr_t
booke_init(u_long arg1, u_long arg2)
{
	uintptr_t ret;
	void *mdp;
	vm_offset_t dtbp, end;

	end = (uintptr_t)_end;
	dtbp = (vm_offset_t)NULL;

	/* Set up TLB initially */
	bootinfo = NULL;
	bzero(__sbss_start, __sbss_end - __sbss_start);
	bzero(__bss_start, _end - __bss_start);
	tlb1_init();

	/*
	 * Handle the various ways we can get loaded and started:
	 *  -	FreeBSD's loader passes the pointer to the metadata
	 *	in arg1, with arg2 undefined. arg1 has a value that's
	 *	relative to the kernel's link address (i.e. larger
	 *	than 0xc0000000).
	 *  -	Juniper's loader passes the metadata pointer in arg2
	 *	and sets arg1 to zero. This is to signal that the
	 *	loader maps the kernel and starts it at its link
	 *	address (unlike the FreeBSD loader).
	 *  -	U-Boot passes the standard argc and argv parameters
	 *	in arg1 and arg2 (resp). arg1 is between 1 and some
	 *	relatively small number, such as 64K. arg2 is the
	 *	physical address of the argv vector.
	 *  -   ePAPR loaders pass an FDT blob in r3 (arg1) and the magic hex
	 *      string 0x45504150 ('EPAP') in r6 (which has been lost by now).
	 *      r4 (arg2) is supposed to be set to zero, but is not always.
	 */
	
	if (arg1 == 0)				/* Juniper loader */
		mdp = (void *)arg2;
	else if (booke_check_for_fdt(arg1, &dtbp) == 0) { /* ePAPR */
		end = roundup(end, 8);
		memmove((void *)end, (void *)dtbp, fdt_totalsize((void *)dtbp));
		dtbp = end;
		end += fdt_totalsize((void *)dtbp);
		__endkernel = end;
		mdp = NULL;
	} else if (arg1 > (uintptr_t)kernload)	/* FreeBSD loader */
		mdp = (void *)arg1;
	else					/* U-Boot */
		mdp = NULL;

	/* Default to 32 byte cache line size. */
	switch ((mfpvr()) >> 16) {
	case FSL_E500mc:
	case FSL_E5500:
	case FSL_E6500:
		cacheline_size = 64;
		break;
	}

	/*
	 * Last element is a magic cookie that indicates that the metadata
	 * pointer is meaningful.
	 */
	ret = powerpc_init(dtbp, 0, 0, mdp, (mdp == NULL) ? 0 : 0xfb5d104d);

	/* Enable caches */
	booke_enable_l1_cache();
	booke_enable_l2_cache();

	booke_enable_bpred();

	return (ret);
}