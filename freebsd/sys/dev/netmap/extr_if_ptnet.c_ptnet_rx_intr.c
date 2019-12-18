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
struct ptnet_softc {int /*<<< orphan*/  ifp; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  intrs; } ;
struct ptnet_queue {int /*<<< orphan*/  kring_id; TYPE_1__ stats; struct ptnet_softc* sc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (int /*<<< orphan*/ ) ; 
 scalar_t__ NM_IRQ_PASS ; 
 int /*<<< orphan*/  PTNET_RX_BUDGET ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ netmap_rx_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  ptnet_rx_eof (struct ptnet_queue*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ptnet_rx_intr(void *opaque)
{
	struct ptnet_queue *pq = opaque;
	struct ptnet_softc *sc = pq->sc;
	unsigned int unused;

	DBG(device_printf(sc->dev, "Rx interrupt #%d\n", pq->kring_id));
#ifdef PTNETMAP_STATS
	pq->stats.intrs ++;
#endif /* PTNETMAP_STATS */

	if (netmap_rx_irq(sc->ifp, pq->kring_id, &unused) != NM_IRQ_PASS) {
		return;
	}

	/* Like vtnet, if_igb and if_em drivers when using MSI-X interrupts,
	 * receive-side processing is executed directly in the interrupt
	 * service routine. Alternatively, we may schedule the taskqueue. */
	ptnet_rx_eof(pq, PTNET_RX_BUDGET, true);
}