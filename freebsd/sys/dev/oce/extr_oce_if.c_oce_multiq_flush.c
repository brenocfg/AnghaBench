#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mbuf {int dummy; } ;
struct ifnet {TYPE_2__* if_softc; } ;
struct TYPE_4__ {int nwqs; TYPE_1__** wq; } ;
struct TYPE_3__ {int /*<<< orphan*/  br; } ;
typedef  TYPE_2__* POCE_SOFTC ;

/* Variables and functions */
 struct mbuf* buf_ring_dequeue_sc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_qflush (struct ifnet*) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 

__attribute__((used)) static void
oce_multiq_flush(struct ifnet *ifp)
{
	POCE_SOFTC sc = ifp->if_softc;
	struct mbuf     *m;
	int i = 0;

	for (i = 0; i < sc->nwqs; i++) {
		while ((m = buf_ring_dequeue_sc(sc->wq[i]->br)) != NULL)
			m_freem(m);
	}
	if_qflush(ifp);
}