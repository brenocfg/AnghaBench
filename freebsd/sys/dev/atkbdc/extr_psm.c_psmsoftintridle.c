#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ inputbytes; } ;
struct psm_softc {scalar_t__ pqueue_start; scalar_t__ pqueue_end; TYPE_3__ idlepacket; TYPE_1__* pqueue; } ;
struct TYPE_4__ {int /*<<< orphan*/ * ipacket; } ;
typedef  TYPE_1__ packetbuf_t ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_DEBUG ; 
 scalar_t__ PSM_PACKETQUEUE ; 
 int /*<<< orphan*/  VLOG (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_3__*,int) ; 
 int /*<<< orphan*/  psmsoftintr (void*) ; 

__attribute__((used)) static void
psmsoftintridle(void *arg)
{
	struct psm_softc *sc = arg;
	packetbuf_t *pb;

	/* Invoke soft handler only when pqueue is empty. Otherwise it will be
	 * invoked from psmintr soon with pqueue filled with real data */
	if (sc->pqueue_start == sc->pqueue_end &&
	    sc->idlepacket.inputbytes > 0) {
		/* Grow circular queue backwards to avoid race with psmintr */
		if (--sc->pqueue_start < 0)
			sc->pqueue_start = PSM_PACKETQUEUE - 1;

		pb = &sc->pqueue[sc->pqueue_start];
		memcpy(pb, &sc->idlepacket, sizeof(packetbuf_t));
		VLOG(4, (LOG_DEBUG,
		    "psmsoftintridle: %02x %02x %02x %02x %02x %02x\n",
		    pb->ipacket[0], pb->ipacket[1], pb->ipacket[2],
		    pb->ipacket[3], pb->ipacket[4], pb->ipacket[5]));

		psmsoftintr(arg);
	}
}