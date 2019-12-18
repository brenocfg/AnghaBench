#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* uma_slab_t ;
typedef  TYPE_2__* uma_keg_t ;
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_10__ {int uk_ppera; int uk_rsize; int uk_flags; int /*<<< orphan*/  (* uk_freef ) (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  uk_slabzone; int /*<<< orphan*/  uk_size; int /*<<< orphan*/  (* uk_fini ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;int /*<<< orphan*/  uk_name; } ;
struct TYPE_9__ {int /*<<< orphan*/ * us_data; int /*<<< orphan*/  us_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTR4 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,TYPE_2__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  KTR_UMA ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  SKIP_NONE ; 
 int UMA_ZONE_OFFPAGE ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trash_fini (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uma_dbg_kskip (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uma_total_dec (int) ; 
 int /*<<< orphan*/  zone_free_item (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
keg_free_slab(uma_keg_t keg, uma_slab_t slab, int start)
{
	uint8_t *mem;
	int i;
	uint8_t flags;

	CTR4(KTR_UMA, "keg_free_slab keg %s(%p) slab %p, returning %d bytes",
	    keg->uk_name, keg, slab, PAGE_SIZE * keg->uk_ppera);

	mem = slab->us_data;
	flags = slab->us_flags;
	i = start;
	if (keg->uk_fini != NULL) {
		for (i--; i > -1; i--)
#ifdef INVARIANTS
		/*
		 * trash_fini implies that dtor was trash_dtor. trash_fini
		 * would check that memory hasn't been modified since free,
		 * which executed trash_dtor.
		 * That's why we need to run uma_dbg_kskip() check here,
		 * albeit we don't make skip check for other init/fini
		 * invocations.
		 */
		if (!uma_dbg_kskip(keg, slab->us_data + (keg->uk_rsize * i)) ||
		    keg->uk_fini != trash_fini)
#endif
			keg->uk_fini(slab->us_data + (keg->uk_rsize * i),
			    keg->uk_size);
	}
	if (keg->uk_flags & UMA_ZONE_OFFPAGE)
		zone_free_item(keg->uk_slabzone, slab, NULL, SKIP_NONE);
	keg->uk_freef(mem, PAGE_SIZE * keg->uk_ppera, flags);
	uma_total_dec(PAGE_SIZE * keg->uk_ppera);
}