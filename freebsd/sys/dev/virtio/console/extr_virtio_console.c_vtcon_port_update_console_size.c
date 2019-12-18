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
typedef  int /*<<< orphan*/  uint16_t ;
struct vtcon_softc_port {struct vtcon_port* vcsp_port; } ;
struct vtcon_softc {struct vtcon_softc_port* vtcon_ports; } ;
struct vtcon_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VTCON_LOCK (struct vtcon_softc*) ; 
 int /*<<< orphan*/  VTCON_PORT_LOCK (struct vtcon_port*) ; 
 int /*<<< orphan*/  VTCON_PORT_UNLOCK (struct vtcon_port*) ; 
 int /*<<< orphan*/  VTCON_UNLOCK (struct vtcon_softc*) ; 
 int /*<<< orphan*/  vtcon_get_console_size (struct vtcon_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vtcon_port_change_size (struct vtcon_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vtcon_port_update_console_size(struct vtcon_softc *sc)
{
	struct vtcon_port *port;
	struct vtcon_softc_port *scport;
	uint16_t cols, rows;

	vtcon_get_console_size(sc, &cols, &rows);

	/*
	 * For now, assume the first (only) port is the console. Note
	 * QEMU does not implement this feature yet.
	 */
	scport = &sc->vtcon_ports[0];

	VTCON_LOCK(sc);
	port = scport->vcsp_port;

	if (port != NULL) {
		VTCON_PORT_LOCK(port);
		VTCON_UNLOCK(sc);
		vtcon_port_change_size(port, cols, rows);
		VTCON_PORT_UNLOCK(port);
	} else
		VTCON_UNLOCK(sc);
}