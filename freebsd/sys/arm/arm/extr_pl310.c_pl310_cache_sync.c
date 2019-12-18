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
struct TYPE_3__ {scalar_t__ sc_rtl_revision; scalar_t__ sc_io_coherent; int /*<<< orphan*/  sc_enabled; } ;

/* Variables and functions */
 scalar_t__ CACHE_ID_RELEASE_r3p0 ; 
 int PL310_CACHE_SYNC ; 
 TYPE_1__* pl310_softc ; 
 int /*<<< orphan*/  pl310_write4 (TYPE_1__*,int,int) ; 

__attribute__((used)) static __inline void
pl310_cache_sync(void)
{

	if ((pl310_softc == NULL) || !pl310_softc->sc_enabled)
		return;

	/* Do not sync outer cache on IO coherent platform */
	if (pl310_softc->sc_io_coherent)
		return;

#ifdef PL310_ERRATA_753970
	if (pl310_softc->sc_rtl_revision == CACHE_ID_RELEASE_r3p0)
		/* Write uncached PL310 register */
		pl310_write4(pl310_softc, 0x740, 0xffffffff);
	else
#endif
		pl310_write4(pl310_softc, PL310_CACHE_SYNC, 0xffffffff);
}