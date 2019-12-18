#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int u_int ;
typedef  TYPE_1__* pmap_t ;
typedef  int /*<<< orphan*/  mmu_t ;
struct TYPE_3__ {int /*<<< orphan*/ * pm_sr; struct TYPE_3__* pmap_phys; int /*<<< orphan*/  pmap_pvo; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int NPMAPS ; 
 int /*<<< orphan*/  RB_INIT (int /*<<< orphan*/ *) ; 
 int VM_MIN_KERNEL_ADDRESS ; 
 int /*<<< orphan*/  VSID_MAKE (int,int) ; 
 int VSID_NBPW ; 
 int ffs (int) ; 
 scalar_t__ moea_kextract (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int* moea_vsid_bitmap ; 
 int /*<<< orphan*/  moea_vsid_mutex ; 
 int moea_vsidcontext ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int rounddown2 (int,int) ; 

void
moea_pinit(mmu_t mmu, pmap_t pmap)
{
	int	i, mask;
	u_int	entropy;

	KASSERT((int)pmap < VM_MIN_KERNEL_ADDRESS, ("moea_pinit: virt pmap"));
	RB_INIT(&pmap->pmap_pvo);

	entropy = 0;
	__asm __volatile("mftb %0" : "=r"(entropy));

	if ((pmap->pmap_phys = (pmap_t)moea_kextract(mmu, (vm_offset_t)pmap))
	    == NULL) {
		pmap->pmap_phys = pmap;
	}


	mtx_lock(&moea_vsid_mutex);
	/*
	 * Allocate some segment registers for this pmap.
	 */
	for (i = 0; i < NPMAPS; i += VSID_NBPW) {
		u_int	hash, n;

		/*
		 * Create a new value by mutiplying by a prime and adding in
		 * entropy from the timebase register.  This is to make the
		 * VSID more random so that the PT hash function collides
		 * less often.  (Note that the prime casues gcc to do shifts
		 * instead of a multiply.)
		 */
		moea_vsidcontext = (moea_vsidcontext * 0x1105) + entropy;
		hash = moea_vsidcontext & (NPMAPS - 1);
		if (hash == 0)		/* 0 is special, avoid it */
			continue;
		n = hash >> 5;
		mask = 1 << (hash & (VSID_NBPW - 1));
		hash = (moea_vsidcontext & 0xfffff);
		if (moea_vsid_bitmap[n] & mask) {	/* collision? */
			/* anything free in this bucket? */
			if (moea_vsid_bitmap[n] == 0xffffffff) {
				entropy = (moea_vsidcontext >> 20);
				continue;
			}
			i = ffs(~moea_vsid_bitmap[n]) - 1;
			mask = 1 << i;
			hash &= rounddown2(0xfffff, VSID_NBPW);
			hash |= i;
		}
		KASSERT(!(moea_vsid_bitmap[n] & mask),
		    ("Allocating in-use VSID group %#x\n", hash));
		moea_vsid_bitmap[n] |= mask;
		for (i = 0; i < 16; i++)
			pmap->pm_sr[i] = VSID_MAKE(i, hash);
		mtx_unlock(&moea_vsid_mutex);
		return;
	}

	mtx_unlock(&moea_vsid_mutex);
	panic("moea_pinit: out of segments");
}