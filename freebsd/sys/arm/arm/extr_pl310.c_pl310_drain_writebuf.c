#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  sc_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  PL310_LOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  PL310_UNLOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  pl310_cache_sync () ; 
 TYPE_1__* pl310_softc ; 

__attribute__((used)) static void
pl310_drain_writebuf(void)
{

	if ((pl310_softc == NULL) || !pl310_softc->sc_enabled)
		return;

	PL310_LOCK(pl310_softc);
	pl310_cache_sync();
	PL310_UNLOCK(pl310_softc);
}