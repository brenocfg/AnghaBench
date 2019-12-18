#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_2__ {scalar_t__ coherent_walk; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARM_SMP_UP (int) ; 
 int PRRR_DS0 ; 
 int PRRR_DS1 ; 
 int PRRR_NS1 ; 
 int TEXDEF_INNER_MASK ; 
 int TEXDEF_INNER_SHIFT ; 
 int TEXDEF_NOS_MASK ; 
 int TEXDEF_NOS_SHIFT ; 
 int TEXDEF_OUTER_MASK ; 
 int TEXDEF_OUTER_SHIFT ; 
 int TEXDEF_TYPE_MASK ; 
 int TEXDEF_TYPE_SHIFT ; 
 int /*<<< orphan*/  VM_MEMATTR_NOCACHE ; 
 int /*<<< orphan*/  VM_MEMATTR_WB_WA ; 
 int /*<<< orphan*/  cp15_nmrr_set (int) ; 
 int /*<<< orphan*/  cp15_prrr_set (int) ; 
 TYPE_1__ cpuinfo ; 
 int /*<<< orphan*/  encode_ttb_flags (int) ; 
 int /*<<< orphan*/  pt_memattr ; 
 int* tex_class ; 
 int /*<<< orphan*/  tlb_flush_all_local () ; 
 int /*<<< orphan*/  ttb_flags ; 

void
pmap_set_tex(void)
{
	uint32_t prrr, nmrr;
	uint32_t type, inner, outer, nos;
	int i;

#ifdef PMAP_PTE_NOCACHE
	/* XXX fixme */
	if (cpuinfo.coherent_walk) {
		pt_memattr = VM_MEMATTR_WB_WA;
		ttb_flags = encode_ttb_flags(0);
	}
	else {
		pt_memattr = VM_MEMATTR_NOCACHE;
		ttb_flags = encode_ttb_flags(1);
	}
#else
	pt_memattr = VM_MEMATTR_WB_WA;
	ttb_flags = encode_ttb_flags(0);
#endif

	prrr = 0;
	nmrr = 0;

	/* Build remapping register from TEX classes. */
	for (i = 0; i < 8; i++) {
		type = (tex_class[i] >> TEXDEF_TYPE_SHIFT) &
			TEXDEF_TYPE_MASK;
		inner = (tex_class[i] >> TEXDEF_INNER_SHIFT) &
			TEXDEF_INNER_MASK;
		outer = (tex_class[i] >> TEXDEF_OUTER_SHIFT) &
			TEXDEF_OUTER_MASK;
		nos = (tex_class[i] >> TEXDEF_NOS_SHIFT) &
			TEXDEF_NOS_MASK;

		prrr |= type  << (i * 2);
		prrr |= nos   << (i + 24);
		nmrr |= inner << (i * 2);
		nmrr |= outer << (i * 2 + 16);
	}
	/* Add shareable bits for device memory. */
	prrr |= PRRR_DS0 | PRRR_DS1;

	/* Add shareable bits for normal memory in SMP case. */
#ifdef SMP
	ARM_SMP_UP(
		prrr |= PRRR_NS1,
	);
#endif
	cp15_prrr_set(prrr);
	cp15_nmrr_set(nmrr);

	/* Caches are disabled, so full TLB flush should be enough. */
	tlb_flush_all_local();
}