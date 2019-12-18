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
typedef  scalar_t__ u_int ;
struct uma_zone_domain {int dummy; } ;
struct uma_zone {int dummy; } ;
struct uma_keg {int dummy; } ;
struct uma_domain {int dummy; } ;
struct uma_cache {int dummy; } ;
struct slabhead {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CACHE_LINE_SIZE ; 
 scalar_t__ PAGE_SIZE ; 
 scalar_t__ SIZEOF_UMA_SLAB ; 
 int /*<<< orphan*/  UMA_BOOT_ALIGN ; 
 int UMA_BOOT_ZONES ; 
 int UMA_HASH_SIZE_INIT ; 
 int UMA_SLAB_SPACE ; 
 int howmany (int,int) ; 
 int ksize ; 
 int mp_maxid ; 
 int roundup (int,int /*<<< orphan*/ ) ; 
 int roundup2 (int,int /*<<< orphan*/ ) ; 
 int vm_ndomains ; 
 int zsize ; 

int
uma_startup_count(int vm_zones)
{
	int zones, pages;

	ksize = sizeof(struct uma_keg) +
	    (sizeof(struct uma_domain) * vm_ndomains);
	zsize = sizeof(struct uma_zone) +
	    (sizeof(struct uma_cache) * (mp_maxid + 1)) +
	    (sizeof(struct uma_zone_domain) * vm_ndomains);

	/*
	 * Memory for the zone of kegs and its keg,
	 * and for zone of zones.
	 */
	pages = howmany(roundup(zsize, CACHE_LINE_SIZE) * 2 +
	    roundup(ksize, CACHE_LINE_SIZE), PAGE_SIZE);

#ifdef	UMA_MD_SMALL_ALLOC
	zones = UMA_BOOT_ZONES;
#else
	zones = UMA_BOOT_ZONES + vm_zones;
	vm_zones = 0;
#endif

	/* Memory for the rest of startup zones, UMA and VM, ... */
	if (zsize > UMA_SLAB_SPACE) {
		/* See keg_large_init(). */
		u_int ppera;

		ppera = howmany(roundup2(zsize, UMA_BOOT_ALIGN), PAGE_SIZE);
		if (PAGE_SIZE * ppera - roundup2(zsize, UMA_BOOT_ALIGN) <
		    SIZEOF_UMA_SLAB)
			ppera++;
		pages += (zones + vm_zones) * ppera;
	} else if (roundup2(zsize, UMA_BOOT_ALIGN) > UMA_SLAB_SPACE)
		/* See keg_small_init() special case for uk_ppera = 1. */
		pages += zones;
	else
		pages += howmany(zones,
		    UMA_SLAB_SPACE / roundup2(zsize, UMA_BOOT_ALIGN));

	/* ... and their kegs. Note that zone of zones allocates a keg! */
	pages += howmany(zones + 1,
	    UMA_SLAB_SPACE / roundup2(ksize, UMA_BOOT_ALIGN));

	/*
	 * Most of startup zones are not going to be offpages, that's
	 * why we use UMA_SLAB_SPACE instead of UMA_SLAB_SIZE in all
	 * calculations.  Some large bucket zones will be offpage, and
	 * thus will allocate hashes.  We take conservative approach
	 * and assume that all zones may allocate hash.  This may give
	 * us some positive inaccuracy, usually an extra single page.
	 */
	pages += howmany(zones, UMA_SLAB_SPACE /
	    (sizeof(struct slabhead *) * UMA_HASH_SIZE_INIT));

	return (pages);
}