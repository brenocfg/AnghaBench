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
struct ptnet_softc {int num_rings; struct ptnet_queue* queues; } ;
struct ptnet_queue {TYPE_1__* atok; } ;
struct netmap_adapter {int /*<<< orphan*/  ifp; } ;
struct TYPE_2__ {int appl_need_kick; } ;

/* Variables and functions */
 struct ptnet_softc* if_getsoftc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ptnet_nm_intr(struct netmap_adapter *na, int onoff)
{
	struct ptnet_softc *sc = if_getsoftc(na->ifp);
	int i;

	for (i = 0; i < sc->num_rings; i++) {
		struct ptnet_queue *pq = sc->queues + i;
		pq->atok->appl_need_kick = onoff;
	}
}