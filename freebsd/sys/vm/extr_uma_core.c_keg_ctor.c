#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* uma_zone_t ;
typedef  TYPE_2__* uma_keg_t ;
struct uma_slab {int dummy; } ;
struct uma_kctor_args {scalar_t__ size; int flags; TYPE_2__* zone; int /*<<< orphan*/  align; int /*<<< orphan*/  fini; int /*<<< orphan*/  uminit; } ;
struct TYPE_12__ {scalar_t__ dr_iter; int /*<<< orphan*/  dr_policy; } ;
struct TYPE_13__ {scalar_t__ uk_size; int uk_pages; int uk_flags; int uk_ppera; int uk_pgoff; int uk_ipers; int /*<<< orphan*/  uk_zones; scalar_t__ uk_free; int /*<<< orphan*/  uz_name; int /*<<< orphan*/  uk_hash; int /*<<< orphan*/  uk_rsize; int /*<<< orphan*/  uk_freef; int /*<<< orphan*/  uk_allocf; int /*<<< orphan*/ * uk_slabzone; int /*<<< orphan*/  uk_init; int /*<<< orphan*/  uk_name; TYPE_1__ uk_dr; scalar_t__ uk_reserve; int /*<<< orphan*/  uk_align; int /*<<< orphan*/  uk_fini; } ;

/* Variables and functions */
 scalar_t__ BOOT_PAGEALLOC ; 
 int /*<<< orphan*/  CTR5 (int /*<<< orphan*/ ,char*,TYPE_2__*,int /*<<< orphan*/ ,TYPE_2__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  DOMAINSET_RR () ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  KEG_LOCK_INIT (TYPE_2__*,int) ; 
 int /*<<< orphan*/  KTR_UMA ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int PAGE_SIZE ; 
 int SIZEOF_UMA_SLAB ; 
 scalar_t__ UMA_SLAB_SPACE ; 
 int UMA_ZFLAG_CACHEONLY ; 
 int UMA_ZONE_CACHESPREAD ; 
 int UMA_ZONE_HASH ; 
 int UMA_ZONE_MALLOC ; 
 int UMA_ZONE_MTXCLASS ; 
 int UMA_ZONE_OFFPAGE ; 
 int UMA_ZONE_PCPU ; 
 int UMA_ZONE_VM ; 
 int UMA_ZONE_VTOSLAB ; 
 int UMA_ZONE_ZINIT ; 
 scalar_t__ booted ; 
 int /*<<< orphan*/  bzero (TYPE_2__*,int) ; 
 int /*<<< orphan*/  hash_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  keg_cachespread_init (TYPE_2__*) ; 
 int /*<<< orphan*/  keg_large_init (TYPE_2__*) ; 
 int /*<<< orphan*/  keg_small_init (TYPE_2__*) ; 
 int /*<<< orphan*/  page_alloc ; 
 int /*<<< orphan*/  page_free ; 
 int /*<<< orphan*/  pcpu_page_alloc ; 
 int /*<<< orphan*/  pcpu_page_free ; 
 int /*<<< orphan*/  rw_wlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_wunlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * slabzone ; 
 int /*<<< orphan*/  startup_alloc ; 
 int /*<<< orphan*/  uk_link ; 
 int /*<<< orphan*/  uma_kegs ; 
 int /*<<< orphan*/  uma_rwlock ; 
 int /*<<< orphan*/  uma_small_alloc ; 
 int /*<<< orphan*/  uma_small_free ; 
 int /*<<< orphan*/  uz_link ; 
 int /*<<< orphan*/  zero_init ; 

__attribute__((used)) static int
keg_ctor(void *mem, int size, void *udata, int flags)
{
	struct uma_kctor_args *arg = udata;
	uma_keg_t keg = mem;
	uma_zone_t zone;

	bzero(keg, size);
	keg->uk_size = arg->size;
	keg->uk_init = arg->uminit;
	keg->uk_fini = arg->fini;
	keg->uk_align = arg->align;
	keg->uk_free = 0;
	keg->uk_reserve = 0;
	keg->uk_pages = 0;
	keg->uk_flags = arg->flags;
	keg->uk_slabzone = NULL;

	/*
	 * We use a global round-robin policy by default.  Zones with
	 * UMA_ZONE_NUMA set will use first-touch instead, in which case the
	 * iterator is never run.
	 */
	keg->uk_dr.dr_policy = DOMAINSET_RR();
	keg->uk_dr.dr_iter = 0;

	/*
	 * The master zone is passed to us at keg-creation time.
	 */
	zone = arg->zone;
	keg->uk_name = zone->uz_name;

	if (arg->flags & UMA_ZONE_VM)
		keg->uk_flags |= UMA_ZFLAG_CACHEONLY;

	if (arg->flags & UMA_ZONE_ZINIT)
		keg->uk_init = zero_init;

	if (arg->flags & UMA_ZONE_MALLOC)
		keg->uk_flags |= UMA_ZONE_VTOSLAB;

	if (arg->flags & UMA_ZONE_PCPU)
#ifdef SMP
		keg->uk_flags |= UMA_ZONE_OFFPAGE;
#else
		keg->uk_flags &= ~UMA_ZONE_PCPU;
#endif

	if (keg->uk_flags & UMA_ZONE_CACHESPREAD) {
		keg_cachespread_init(keg);
	} else {
		if (keg->uk_size > UMA_SLAB_SPACE)
			keg_large_init(keg);
		else
			keg_small_init(keg);
	}

	if (keg->uk_flags & UMA_ZONE_OFFPAGE)
		keg->uk_slabzone = slabzone;

	/*
	 * If we haven't booted yet we need allocations to go through the
	 * startup cache until the vm is ready.
	 */
	if (booted < BOOT_PAGEALLOC)
		keg->uk_allocf = startup_alloc;
#ifdef UMA_MD_SMALL_ALLOC
	else if (keg->uk_ppera == 1)
		keg->uk_allocf = uma_small_alloc;
#endif
	else if (keg->uk_flags & UMA_ZONE_PCPU)
		keg->uk_allocf = pcpu_page_alloc;
	else
		keg->uk_allocf = page_alloc;
#ifdef UMA_MD_SMALL_ALLOC
	if (keg->uk_ppera == 1)
		keg->uk_freef = uma_small_free;
	else
#endif
	if (keg->uk_flags & UMA_ZONE_PCPU)
		keg->uk_freef = pcpu_page_free;
	else
		keg->uk_freef = page_free;

	/*
	 * Initialize keg's lock
	 */
	KEG_LOCK_INIT(keg, (arg->flags & UMA_ZONE_MTXCLASS));

	/*
	 * If we're putting the slab header in the actual page we need to
	 * figure out where in each page it goes.  See SIZEOF_UMA_SLAB
	 * macro definition.
	 */
	if (!(keg->uk_flags & UMA_ZONE_OFFPAGE)) {
		keg->uk_pgoff = (PAGE_SIZE * keg->uk_ppera) - SIZEOF_UMA_SLAB;
		/*
		 * The only way the following is possible is if with our
		 * UMA_ALIGN_PTR adjustments we are now bigger than
		 * UMA_SLAB_SIZE.  I haven't checked whether this is
		 * mathematically possible for all cases, so we make
		 * sure here anyway.
		 */
		KASSERT(keg->uk_pgoff + sizeof(struct uma_slab) <=
		    PAGE_SIZE * keg->uk_ppera,
		    ("zone %s ipers %d rsize %d size %d slab won't fit",
		    zone->uz_name, keg->uk_ipers, keg->uk_rsize, keg->uk_size));
	}

	if (keg->uk_flags & UMA_ZONE_HASH)
		hash_alloc(&keg->uk_hash, 0);

	CTR5(KTR_UMA, "keg_ctor %p zone %s(%p) out %d free %d\n",
	    keg, zone->uz_name, zone,
	    (keg->uk_pages / keg->uk_ppera) * keg->uk_ipers - keg->uk_free,
	    keg->uk_free);

	LIST_INSERT_HEAD(&keg->uk_zones, zone, uz_link);

	rw_wlock(&uma_rwlock);
	LIST_INSERT_HEAD(&uma_kegs, keg, uk_link);
	rw_wunlock(&uma_rwlock);
	return (0);
}