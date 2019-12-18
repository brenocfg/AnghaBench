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
struct task {int dummy; } ;
struct ifnet {int dummy; } ;
struct hn_softc {int hn_rx_ring_cnt; int hn_rx_ring_inuse; struct hn_rx_ring* hn_rx_ring; } ;
struct hn_rxvf_setarg {struct ifnet* vf_ifp; struct hn_rx_ring* rxr; } ;
struct hn_rx_ring {struct ifnet* hn_rxvf_ifp; int /*<<< orphan*/  hn_chan; } ;

/* Variables and functions */
 int /*<<< orphan*/  HN_LOCK_ASSERT (struct hn_softc*) ; 
 int /*<<< orphan*/  TASK_INIT (struct task*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct hn_rxvf_setarg*) ; 
 int /*<<< orphan*/  hn_rxvf_set_task ; 
 int /*<<< orphan*/  vmbus_chan_run_task (int /*<<< orphan*/ ,struct task*) ; 

__attribute__((used)) static void
hn_rxvf_set(struct hn_softc *sc, struct ifnet *vf_ifp)
{
	struct hn_rx_ring *rxr;
	struct hn_rxvf_setarg arg;
	struct task task;
	int i;

	HN_LOCK_ASSERT(sc);

	TASK_INIT(&task, 0, hn_rxvf_set_task, &arg);

	for (i = 0; i < sc->hn_rx_ring_cnt; ++i) {
		rxr = &sc->hn_rx_ring[i];

		if (i < sc->hn_rx_ring_inuse) {
			arg.rxr = rxr;
			arg.vf_ifp = vf_ifp;
			vmbus_chan_run_task(rxr->hn_chan, &task);
		} else {
			rxr->hn_rxvf_ifp = vf_ifp;
		}
	}
}