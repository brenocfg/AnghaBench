#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct hn_softc {int hn_rx_ring_cnt; TYPE_1__* hn_rx_ring; int /*<<< orphan*/  hn_vf_lock; int /*<<< orphan*/ * hn_vf_ifp; int /*<<< orphan*/  hn_xvf_flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  hn_rx_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  HN_LOCK_ASSERT (struct hn_softc*) ; 
 int /*<<< orphan*/  HN_RX_FLAG_XPNT_VF ; 
 int /*<<< orphan*/  HN_XVFFLAG_ENABLED ; 
 int /*<<< orphan*/  rm_wlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rm_wunlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
hn_xpnt_vf_setdisable(struct hn_softc *sc, bool clear_vf)
{
	int i;

	HN_LOCK_ASSERT(sc);

	/* NOTE: hn_vf_lock for hn_transmit()/hn_qflush() */
	rm_wlock(&sc->hn_vf_lock);
	sc->hn_xvf_flags &= ~HN_XVFFLAG_ENABLED;
	if (clear_vf)
		sc->hn_vf_ifp = NULL;
	rm_wunlock(&sc->hn_vf_lock);

	for (i = 0; i < sc->hn_rx_ring_cnt; ++i)
		sc->hn_rx_ring[i].hn_rx_flags &= ~HN_RX_FLAG_XPNT_VF;
}