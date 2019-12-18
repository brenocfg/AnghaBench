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
struct TYPE_2__ {struct stge_rfd* stge_rx_ring; } ;
struct stge_softc {TYPE_1__ sc_rdata; } ;
struct stge_rfd {scalar_t__ rfd_status; } ;

/* Variables and functions */

__attribute__((used)) static __inline void
stge_discard_rxbuf(struct stge_softc *sc, int idx)
{
	struct stge_rfd *rfd;

	rfd = &sc->sc_rdata.stge_rx_ring[idx];
	rfd->rfd_status = 0;
}