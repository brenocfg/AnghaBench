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
struct vtcon_softc_port {struct vtcon_port* vcsp_port; } ;
struct vtcon_softc {struct vtcon_softc_port* vtcon_ports; int /*<<< orphan*/  vtcon_dev; } ;
struct vtcon_port {int vtcport_id; int /*<<< orphan*/  vtcport_tty; int /*<<< orphan*/  vtcport_mtx; struct vtcon_softc_port* vtcport_scport; struct vtcon_softc* vtcport_sc; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  MPASS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  VIRTIO_CONSOLE_PORT_READY ; 
 int /*<<< orphan*/  VTCON_ASSERT_VALID_PORTID (struct vtcon_softc*,int) ; 
 int /*<<< orphan*/  VTCON_LOCK (struct vtcon_softc*) ; 
 int /*<<< orphan*/  VTCON_PORT_LOCK (struct vtcon_port*) ; 
 int /*<<< orphan*/  VTCON_PORT_UNLOCK (struct vtcon_port*) ; 
 int /*<<< orphan*/  VTCON_TTY_PREFIX ; 
 int /*<<< orphan*/  VTCON_UNLOCK (struct vtcon_softc*) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 struct vtcon_port* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_alloc_mutex (int /*<<< orphan*/ *,struct vtcon_port*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_makedev (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vtcon_port_enable_intr (struct vtcon_port*) ; 
 int vtcon_port_init_vqs (struct vtcon_port*) ; 
 int /*<<< orphan*/  vtcon_port_submit_event (struct vtcon_port*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vtcon_port_teardown (struct vtcon_port*) ; 
 int /*<<< orphan*/  vtcon_tty_class ; 

__attribute__((used)) static int
vtcon_port_create(struct vtcon_softc *sc, int id)
{
	device_t dev;
	struct vtcon_softc_port *scport;
	struct vtcon_port *port;
	int error;

	dev = sc->vtcon_dev;
	scport = &sc->vtcon_ports[id];

	VTCON_ASSERT_VALID_PORTID(sc, id);
	MPASS(scport->vcsp_port == NULL);

	port = malloc(sizeof(struct vtcon_port), M_DEVBUF, M_NOWAIT | M_ZERO);
	if (port == NULL)
		return (ENOMEM);

	port->vtcport_sc = sc;
	port->vtcport_scport = scport;
	port->vtcport_id = id;
	mtx_init(&port->vtcport_mtx, "vtcpmtx", NULL, MTX_DEF);
	port->vtcport_tty = tty_alloc_mutex(&vtcon_tty_class, port,
	    &port->vtcport_mtx);

	error = vtcon_port_init_vqs(port);
	if (error) {
		VTCON_PORT_LOCK(port);
		vtcon_port_teardown(port);
		return (error);
	}

	VTCON_LOCK(sc);
	VTCON_PORT_LOCK(port);
	scport->vcsp_port = port;
	vtcon_port_enable_intr(port);
	vtcon_port_submit_event(port, VIRTIO_CONSOLE_PORT_READY, 1);
	VTCON_PORT_UNLOCK(port);
	VTCON_UNLOCK(sc);

	tty_makedev(port->vtcport_tty, NULL, "%s%r.%r", VTCON_TTY_PREFIX,
	    device_get_unit(dev), id);

	return (0);
}