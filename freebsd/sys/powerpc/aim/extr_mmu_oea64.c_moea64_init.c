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
struct pvo_entry {int dummy; } ;
typedef  int /*<<< orphan*/  mmu_t ;

/* Variables and functions */
 int /*<<< orphan*/  CTR0 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  KTR_PMAP ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  UMA_ALIGN_PTR ; 
 int UMA_ZONE_NOFREE ; 
 int UMA_ZONE_VM ; 
 int elf32_nxstack ; 
 int /*<<< orphan*/  hw_direct_map ; 
 int /*<<< orphan*/  installed_mmu ; 
 int /*<<< orphan*/  moea64_initialized ; 
 int /*<<< orphan*/  moea64_pvo_zone ; 
 int /*<<< orphan*/  moea64_uma_page_alloc ; 
 int /*<<< orphan*/  uma_zcreate (char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uma_zone_set_allocf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
moea64_init(mmu_t mmu)
{

	CTR0(KTR_PMAP, "moea64_init");

	moea64_pvo_zone = uma_zcreate("UPVO entry", sizeof (struct pvo_entry),
	    NULL, NULL, NULL, NULL, UMA_ALIGN_PTR,
	    UMA_ZONE_VM | UMA_ZONE_NOFREE);

	if (!hw_direct_map) {
		installed_mmu = mmu;
		uma_zone_set_allocf(moea64_pvo_zone, moea64_uma_page_alloc);
	}

#ifdef COMPAT_FREEBSD32
	elf32_nxstack = 1;
#endif

	moea64_initialized = TRUE;
}