#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int vm_size_t ;
typedef  int vm_paddr_t ;
struct TYPE_6__ {scalar_t__ sc_rtl_revision; int /*<<< orphan*/  sc_enabled; } ;

/* Variables and functions */
 scalar_t__ CACHE_ID_RELEASE_r1p0 ; 
 scalar_t__ CACHE_ID_RELEASE_r2p0 ; 
 scalar_t__ CACHE_ID_RELEASE_r3p1 ; 
 int /*<<< orphan*/  PL310_CLEAN_INV_LINE_PA ; 
 int /*<<< orphan*/  PL310_CLEAN_LINE_PA ; 
 int /*<<< orphan*/  PL310_INV_LINE_PA ; 
 int /*<<< orphan*/  PL310_LOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  PL310_UNLOCK (TYPE_1__*) ; 
 int g_l2cache_align_mask ; 
 scalar_t__ g_l2cache_line_size ; 
 int /*<<< orphan*/  pl310_cache_sync () ; 
 TYPE_1__* pl310_softc ; 
 int /*<<< orphan*/  pl310_write4 (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  platform_pl310_write_debug (TYPE_1__*,int) ; 

__attribute__((used)) static void
pl310_wbinv_range(vm_paddr_t start, vm_size_t size)
{

	if ((pl310_softc == NULL) || !pl310_softc->sc_enabled)
		return;

	PL310_LOCK(pl310_softc);
	if (start & g_l2cache_align_mask) {
		size += start & g_l2cache_align_mask;
		start &= ~g_l2cache_align_mask;
	}
	if (size & g_l2cache_align_mask) {
		size &= ~g_l2cache_align_mask;
	   	size += g_l2cache_line_size;
	}


#ifdef PL310_ERRATA_727915
	if (pl310_softc->sc_rtl_revision >= CACHE_ID_RELEASE_r2p0 &&
	    pl310_softc->sc_rtl_revision < CACHE_ID_RELEASE_r3p1)
		platform_pl310_write_debug(pl310_softc, 3);
#endif
	while (size > 0) {
#ifdef PL310_ERRATA_588369
		if (pl310_softc->sc_rtl_revision <= CACHE_ID_RELEASE_r1p0) {
			/*
			 * Errata 588369 says that clean + inv may keep the
			 * cache line if it was clean, the recommanded
			 * workaround is to clean then invalidate the cache
			 * line, with write-back and cache linefill disabled.
			 */
			pl310_write4(pl310_softc, PL310_CLEAN_LINE_PA, start);
			pl310_write4(pl310_softc, PL310_INV_LINE_PA, start);
		} else
#endif
			pl310_write4(pl310_softc, PL310_CLEAN_INV_LINE_PA,
			    start);
		start += g_l2cache_line_size;
		size -= g_l2cache_line_size;
	}
#ifdef PL310_ERRATA_727915
	if (pl310_softc->sc_rtl_revision >= CACHE_ID_RELEASE_r2p0 &&
	    pl310_softc->sc_rtl_revision < CACHE_ID_RELEASE_r3p1)
		platform_pl310_write_debug(pl310_softc, 0);
#endif

	pl310_cache_sync();
	PL310_UNLOCK(pl310_softc);
}