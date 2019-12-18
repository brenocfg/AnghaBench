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
struct vtcon_softc_port {struct virtqueue* vcsp_invq; struct vtcon_port* vcsp_port; } ;
struct vtcon_softc {int vtcon_max_ports; struct vtcon_softc_port* vtcon_ports; } ;
struct vtcon_port {int dummy; } ;
struct virtqueue {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  VTCON_LOCK (struct vtcon_softc*) ; 
 int /*<<< orphan*/  VTCON_PORT_LOCK (struct vtcon_port*) ; 
 int /*<<< orphan*/  VTCON_UNLOCK (struct vtcon_softc*) ; 
 int /*<<< orphan*/  free (struct vtcon_softc_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vtcon_port_drain_bufs (struct virtqueue*) ; 
 int /*<<< orphan*/  vtcon_port_teardown (struct vtcon_port*) ; 

__attribute__((used)) static void
vtcon_destroy_ports(struct vtcon_softc *sc)
{
	struct vtcon_softc_port *scport;
	struct vtcon_port *port;
	struct virtqueue *vq;
	int i;

	if (sc->vtcon_ports == NULL)
		return;

	VTCON_LOCK(sc);
	for (i = 0; i < sc->vtcon_max_ports; i++) {
		scport = &sc->vtcon_ports[i];

		port = scport->vcsp_port;
		if (port != NULL) {
			scport->vcsp_port = NULL;
			VTCON_PORT_LOCK(port);
			VTCON_UNLOCK(sc);
			vtcon_port_teardown(port);
			VTCON_LOCK(sc);
		}

		vq = scport->vcsp_invq;
		if (vq != NULL)
			vtcon_port_drain_bufs(vq);
	}
	VTCON_UNLOCK(sc);

	free(sc->vtcon_ports, M_DEVBUF);
	sc->vtcon_ports = NULL;
}