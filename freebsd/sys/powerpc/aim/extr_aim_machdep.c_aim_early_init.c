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
typedef  scalar_t__ vm_offset_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  register_t ;

/* Variables and functions */
 scalar_t__ DMAP_BASE_ADDRESS ; 
 int /*<<< orphan*/  HID5_970_DCBZ_SIZE_HI ; 
#define  IBM970 137 
#define  IBM970FX 136 
#define  IBM970GX 135 
#define  IBM970MP 134 
#define  IBMPOWER7 133 
#define  IBMPOWER7PLUS 132 
#define  IBMPOWER8 131 
#define  IBMPOWER8E 130 
#define  IBMPOWER8NVL 129 
#define  IBMPOWER9 128 
 int PSL_DR ; 
 int PSL_IR ; 
 int /*<<< orphan*/  SPR_HID5 ; 
 int /*<<< orphan*/  __restartkernel (scalar_t__,int /*<<< orphan*/ ,scalar_t__,void*,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int mfmsr () ; 
 int mfpvr () ; 
 int /*<<< orphan*/  mfspr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtmsr (int) ; 
 int /*<<< orphan*/  mtspr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int n_slbs ; 

void
aim_early_init(vm_offset_t fdt, vm_offset_t toc, vm_offset_t ofentry, void *mdp,
    uint32_t mdp_cookie)
{
	register_t	scratch;

	/*
	 * If running from an FDT, make sure we are in real mode to avoid
	 * tromping on firmware page tables. Everything in the kernel assumes
	 * 1:1 mappings out of firmware, so this won't break anything not
	 * already broken. This doesn't work if there is live OF, since OF
	 * may internally use non-1:1 mappings.
	 */
	if (ofentry == 0)
		mtmsr(mfmsr() & ~(PSL_IR | PSL_DR));

#ifdef __powerpc64__
	/*
	 * If in real mode, relocate to high memory so that the kernel
	 * can execute from the direct map.
	 */
	if (!(mfmsr() & PSL_DR) &&
	    (vm_offset_t)&aim_early_init < DMAP_BASE_ADDRESS)
		__restartkernel(fdt, 0, ofentry, mdp, mdp_cookie,
		    DMAP_BASE_ADDRESS, mfmsr());
#endif

	/* Various very early CPU fix ups */
	switch (mfpvr() >> 16) {
		/*
		 * PowerPC 970 CPUs have a misfeature requested by Apple that
		 * makes them pretend they have a 32-byte cacheline. Turn this
		 * off before we measure the cacheline size.
		 */
		case IBM970:
		case IBM970FX:
		case IBM970MP:
		case IBM970GX:
			scratch = mfspr(SPR_HID5);
			scratch &= ~HID5_970_DCBZ_SIZE_HI;
			mtspr(SPR_HID5, scratch);
			break;
	#ifdef __powerpc64__
		case IBMPOWER7:
		case IBMPOWER7PLUS:
		case IBMPOWER8:
		case IBMPOWER8E:
		case IBMPOWER8NVL:
		case IBMPOWER9:
			/* XXX: get from ibm,slb-size in device tree */
			n_slbs = 32;
			break;
	#endif
	}
}