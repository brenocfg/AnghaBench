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
struct vtcon_softc_port {struct vtcon_port* vcsp_port; struct vtcon_softc* vcsp_sc; } ;
struct vtcon_softc {int dummy; } ;
struct vtcon_port {int vtcport_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  VTCON_LOCK (struct vtcon_softc*) ; 
 int VTCON_PORT_FLAG_GONE ; 
 int /*<<< orphan*/  VTCON_PORT_LOCK (struct vtcon_port*) ; 
 int /*<<< orphan*/  VTCON_PORT_UNLOCK (struct vtcon_port*) ; 
 int /*<<< orphan*/  VTCON_UNLOCK (struct vtcon_softc*) ; 
 int /*<<< orphan*/  vtcon_port_in (struct vtcon_port*) ; 

__attribute__((used)) static void
vtcon_port_intr(void *scportx)
{
	struct vtcon_softc_port *scport;
	struct vtcon_softc *sc;
	struct vtcon_port *port;

	scport = scportx;
	sc = scport->vcsp_sc;

	VTCON_LOCK(sc);
	port = scport->vcsp_port;
	if (port == NULL) {
		VTCON_UNLOCK(sc);
		return;
	}
	VTCON_PORT_LOCK(port);
	VTCON_UNLOCK(sc);
	if ((port->vtcport_flags & VTCON_PORT_FLAG_GONE) == 0)
		vtcon_port_in(port);
	VTCON_PORT_UNLOCK(port);
}