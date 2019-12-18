#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* uma_zone_t ;
struct TYPE_16__ {scalar_t__ uz_max_items; scalar_t__ uz_items; scalar_t__ uz_sleepers; int (* uz_import ) (int /*<<< orphan*/ ,void**,int,int,int) ;scalar_t__ (* uz_init ) (void*,int /*<<< orphan*/ ,int) ;scalar_t__ (* uz_ctor ) (void*,int /*<<< orphan*/ ,void*,int) ;scalar_t__ uz_dtor; int /*<<< orphan*/  uz_name; int /*<<< orphan*/  uz_fails; int /*<<< orphan*/  uz_allocs; int /*<<< orphan*/  uz_size; int /*<<< orphan*/  uz_arg; int /*<<< orphan*/  uz_lockptr; int /*<<< orphan*/  uz_sleeps; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTR2 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  CTR3 (int /*<<< orphan*/ ,char*,void*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  KTR_UMA ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  PVM ; 
 int SKIP_CNT ; 
 int SKIP_DTOR ; 
 int SKIP_FINI ; 
 int UMA_ANYDOMAIN ; 
 scalar_t__ VM_DOMAIN_EMPTY (int) ; 
 int /*<<< orphan*/  ZONE_LOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  ZONE_LOCK_ASSERT (TYPE_1__*) ; 
 int /*<<< orphan*/  ZONE_UNLOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  counter_u64_add (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_sleep (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ ,void**,int,int,int) ; 
 scalar_t__ stub2 (void*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub3 (void*,int /*<<< orphan*/ ,void*,int) ; 
 scalar_t__ trash_ctor (void*,int /*<<< orphan*/ ,void*,int) ; 
 scalar_t__ trash_dtor ; 
 int /*<<< orphan*/  uma_dbg_alloc (TYPE_1__*,int /*<<< orphan*/ *,void*) ; 
 int uma_dbg_zskip (TYPE_1__*,void*) ; 
 int /*<<< orphan*/  uma_zero_item (void*,TYPE_1__*) ; 
 int /*<<< orphan*/  wakeup_one (TYPE_1__*) ; 
 int /*<<< orphan*/  zone_free_item (TYPE_1__*,void*,void*,int) ; 
 int /*<<< orphan*/  zone_log_warning (TYPE_1__*) ; 
 int /*<<< orphan*/  zone_maxaction (TYPE_1__*) ; 

__attribute__((used)) static void *
zone_alloc_item_locked(uma_zone_t zone, void *udata, int domain, int flags)
{
	void *item;
#ifdef INVARIANTS
	bool skipdbg;
#endif

	ZONE_LOCK_ASSERT(zone);

	if (zone->uz_max_items > 0) {
		if (zone->uz_items >= zone->uz_max_items) {
			zone_log_warning(zone);
			zone_maxaction(zone);
			if (flags & M_NOWAIT) {
				ZONE_UNLOCK(zone);
				return (NULL);
			}
			zone->uz_sleeps++;
			zone->uz_sleepers++;
			while (zone->uz_items >= zone->uz_max_items)
				mtx_sleep(zone, zone->uz_lockptr, PVM,
				    "zonelimit", 0);
			zone->uz_sleepers--;
			if (zone->uz_sleepers > 0 &&
			    zone->uz_items + 1 < zone->uz_max_items)
				wakeup_one(zone);
		}
		zone->uz_items++;
	}
	ZONE_UNLOCK(zone);

	/* Avoid allocs targeting empty domains. */
	if (domain != UMA_ANYDOMAIN && VM_DOMAIN_EMPTY(domain))
		domain = UMA_ANYDOMAIN;

	if (zone->uz_import(zone->uz_arg, &item, 1, domain, flags) != 1)
		goto fail;

#ifdef INVARIANTS
	skipdbg = uma_dbg_zskip(zone, item);
#endif
	/*
	 * We have to call both the zone's init (not the keg's init)
	 * and the zone's ctor.  This is because the item is going from
	 * a keg slab directly to the user, and the user is expecting it
	 * to be both zone-init'd as well as zone-ctor'd.
	 */
	if (zone->uz_init != NULL) {
		if (zone->uz_init(item, zone->uz_size, flags) != 0) {
			zone_free_item(zone, item, udata, SKIP_FINI | SKIP_CNT);
			goto fail;
		}
	}
	if (zone->uz_ctor != NULL &&
#ifdef INVARIANTS
	    (!skipdbg || zone->uz_ctor != trash_ctor ||
	    zone->uz_dtor != trash_dtor) &&
#endif
	    zone->uz_ctor(item, zone->uz_size, udata, flags) != 0) {
		zone_free_item(zone, item, udata, SKIP_DTOR | SKIP_CNT);
		goto fail;
	}
#ifdef INVARIANTS
	if (!skipdbg)
		uma_dbg_alloc(zone, NULL, item);
#endif
	if (flags & M_ZERO)
		uma_zero_item(item, zone);

	counter_u64_add(zone->uz_allocs, 1);
	CTR3(KTR_UMA, "zone_alloc_item item %p from %s(%p)", item,
	    zone->uz_name, zone);

	return (item);

fail:
	if (zone->uz_max_items > 0) {
		ZONE_LOCK(zone);
		zone->uz_items--;
		ZONE_UNLOCK(zone);
	}
	counter_u64_add(zone->uz_fails, 1);
	CTR2(KTR_UMA, "zone_alloc_item failed from %s(%p)",
	    zone->uz_name, zone);
	return (NULL);
}