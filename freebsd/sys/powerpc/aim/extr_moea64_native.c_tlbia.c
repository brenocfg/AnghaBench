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
typedef  int vm_offset_t ;
typedef  int /*<<< orphan*/  register_t ;

/* Variables and functions */
 int /*<<< orphan*/  EIEIO () ; 
#define  IBM970 135 
#define  IBM970FX 134 
#define  IBM970GX 133 
#define  IBM970MP 132 
#define  IBMPOWER4 131 
#define  IBMPOWER4PLUS 130 
#define  IBMPOWER5 129 
#define  IBMPOWER5PLUS 128 
 int /*<<< orphan*/  TLBSYNC () ; 
 int mfpvr () ; 

__attribute__((used)) static void
tlbia(void)
{
	vm_offset_t i;
	#ifndef __powerpc64__
	register_t msr, scratch;
	#endif

	i = 0xc00; /* IS = 11 */
	switch (mfpvr() >> 16) {
	case IBM970:
	case IBM970FX:
	case IBM970MP:
	case IBM970GX:
	case IBMPOWER4:
	case IBMPOWER4PLUS:
	case IBMPOWER5:
	case IBMPOWER5PLUS:
		i = 0; /* IS not supported */
		break;
	}

	TLBSYNC();

	for (; i < 0x400000; i += 0x00001000) {
		#ifdef __powerpc64__
		__asm __volatile("tlbiel %0" :: "r"(i));
		#else
		__asm __volatile("\
		    mfmsr %0; \
		    mr %1, %0; \
		    insrdi %1,%3,1,0; \
		    mtmsrd %1; \
		    isync; \
		    \
		    tlbiel %2; \
		    \
		    mtmsrd %0; \
		    isync;" 
		: "=r"(msr), "=r"(scratch) : "r"(i), "r"(1));
		#endif
	}

	EIEIO();
	TLBSYNC();
}