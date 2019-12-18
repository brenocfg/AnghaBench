#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_offset_t ;
typedef  TYPE_1__* uma_zone_t ;
typedef  TYPE_2__* uma_slab_t ;
typedef  TYPE_3__* uma_keg_t ;
typedef  int /*<<< orphan*/ * (* uma_alloc ) (TYPE_1__*,unsigned long,int,int /*<<< orphan*/ *,int) ;
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_21__ {int uk_flags; int uk_ppera; int uk_pgoff; int uk_ipers; scalar_t__ (* uk_init ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ;int uk_rsize; int uk_pages; int uk_free; int /*<<< orphan*/  uk_hash; int /*<<< orphan*/  uk_name; int /*<<< orphan*/  uk_size; int /*<<< orphan*/  uk_slabzone; int /*<<< orphan*/ * (* uk_allocf ) (TYPE_1__*,unsigned long,int,int /*<<< orphan*/ *,int) ;int /*<<< orphan*/  uk_lock; } ;
struct TYPE_20__ {int us_freecount; int us_domain; int /*<<< orphan*/ * us_data; int /*<<< orphan*/  us_debugfree; int /*<<< orphan*/  us_free; int /*<<< orphan*/  us_flags; TYPE_3__* us_keg; } ;
struct TYPE_19__ {int /*<<< orphan*/ * uz_lockptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_FILL (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIT_ZERO (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CTR3 (int /*<<< orphan*/ ,char*,TYPE_2__*,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  KEG_LOCK (TYPE_3__*) ; 
 int /*<<< orphan*/  KEG_LOCK_ASSERT (TYPE_3__*) ; 
 int /*<<< orphan*/  KEG_UNLOCK (TYPE_3__*) ; 
 int /*<<< orphan*/  KTR_UMA ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int M_NODUMP ; 
 int M_ZERO ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  SKIP_NONE ; 
 int /*<<< orphan*/  SLAB_SETSIZE ; 
 int /*<<< orphan*/  UMA_HASH_INSERT (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int UMA_ZONE_HASH ; 
 int UMA_ZONE_MALLOC ; 
 int UMA_ZONE_NODUMP ; 
 int UMA_ZONE_OFFPAGE ; 
 int UMA_ZONE_VTOSLAB ; 
 int /*<<< orphan*/  keg_free_slab (TYPE_3__*,TYPE_2__*,int) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uma_total_inc (unsigned long) ; 
 int vm_ndomains ; 
 int /*<<< orphan*/  vsetslab (scalar_t__,TYPE_2__*) ; 
 TYPE_2__* zone_alloc_item (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  zone_free_item (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uma_slab_t
keg_alloc_slab(uma_keg_t keg, uma_zone_t zone, int domain, int flags,
    int aflags)
{
	uma_alloc allocf;
	uma_slab_t slab;
	unsigned long size;
	uint8_t *mem;
	uint8_t sflags;
	int i;

	KASSERT(domain >= 0 && domain < vm_ndomains,
	    ("keg_alloc_slab: domain %d out of range", domain));
	KEG_LOCK_ASSERT(keg);
	MPASS(zone->uz_lockptr == &keg->uk_lock);

	allocf = keg->uk_allocf;
	KEG_UNLOCK(keg);

	slab = NULL;
	mem = NULL;
	if (keg->uk_flags & UMA_ZONE_OFFPAGE) {
		slab = zone_alloc_item(keg->uk_slabzone, NULL, domain, aflags);
		if (slab == NULL)
			goto out;
	}

	/*
	 * This reproduces the old vm_zone behavior of zero filling pages the
	 * first time they are added to a zone.
	 *
	 * Malloced items are zeroed in uma_zalloc.
	 */

	if ((keg->uk_flags & UMA_ZONE_MALLOC) == 0)
		aflags |= M_ZERO;
	else
		aflags &= ~M_ZERO;

	if (keg->uk_flags & UMA_ZONE_NODUMP)
		aflags |= M_NODUMP;

	/* zone is passed for legacy reasons. */
	size = keg->uk_ppera * PAGE_SIZE;
	mem = allocf(zone, size, domain, &sflags, aflags);
	if (mem == NULL) {
		if (keg->uk_flags & UMA_ZONE_OFFPAGE)
			zone_free_item(keg->uk_slabzone, slab, NULL, SKIP_NONE);
		slab = NULL;
		goto out;
	}
	uma_total_inc(size);

	/* Point the slab into the allocated memory */
	if (!(keg->uk_flags & UMA_ZONE_OFFPAGE))
		slab = (uma_slab_t )(mem + keg->uk_pgoff);

	if (keg->uk_flags & UMA_ZONE_VTOSLAB)
		for (i = 0; i < keg->uk_ppera; i++)
			vsetslab((vm_offset_t)mem + (i * PAGE_SIZE), slab);

	slab->us_keg = keg;
	slab->us_data = mem;
	slab->us_freecount = keg->uk_ipers;
	slab->us_flags = sflags;
	slab->us_domain = domain;
	BIT_FILL(SLAB_SETSIZE, &slab->us_free);
#ifdef INVARIANTS
	BIT_ZERO(SLAB_SETSIZE, &slab->us_debugfree);
#endif

	if (keg->uk_init != NULL) {
		for (i = 0; i < keg->uk_ipers; i++)
			if (keg->uk_init(slab->us_data + (keg->uk_rsize * i),
			    keg->uk_size, flags) != 0)
				break;
		if (i != keg->uk_ipers) {
			keg_free_slab(keg, slab, i);
			slab = NULL;
			goto out;
		}
	}
	KEG_LOCK(keg);

	CTR3(KTR_UMA, "keg_alloc_slab: allocated slab %p for %s(%p)",
	    slab, keg->uk_name, keg);

	if (keg->uk_flags & UMA_ZONE_HASH)
		UMA_HASH_INSERT(&keg->uk_hash, slab, mem);

	keg->uk_pages += keg->uk_ppera;
	keg->uk_free += keg->uk_ipers;

out:
	return (slab);
}