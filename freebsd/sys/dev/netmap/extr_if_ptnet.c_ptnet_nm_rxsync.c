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
struct ptnet_softc {struct ptnet_queue* rxqueues; } ;
struct ptnet_queue {int /*<<< orphan*/  ktoa; int /*<<< orphan*/  atok; } ;
struct netmap_kring {int ring_id; TYPE_1__* na; } ;
struct TYPE_2__ {int /*<<< orphan*/  ifp; } ;

/* Variables and functions */
 struct ptnet_softc* if_getsoftc (int /*<<< orphan*/ ) ; 
 int netmap_pt_guest_rxsync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct netmap_kring*,int) ; 
 int /*<<< orphan*/  ptnet_kick (struct ptnet_queue*) ; 

__attribute__((used)) static int
ptnet_nm_rxsync(struct netmap_kring *kring, int flags)
{
	struct ptnet_softc *sc = if_getsoftc(kring->na->ifp);
	struct ptnet_queue *pq = sc->rxqueues + kring->ring_id;
	bool notify;

	notify = netmap_pt_guest_rxsync(pq->atok, pq->ktoa, kring, flags);
	if (notify) {
		ptnet_kick(pq);
	}

	return 0;
}