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
struct pci_vtcon_softc {int vsc_nports; struct pci_vtcon_port* vsc_ports; } ;
struct pci_vtcon_port {int vsp_id; char const* vsp_name; int vsp_txq; int vsp_rxq; int vsp_enabled; void* vsp_arg; int /*<<< orphan*/ * vsp_cb; struct pci_vtcon_softc* vsp_sc; } ;
typedef  int /*<<< orphan*/  pci_vtcon_cb_t ;

/* Variables and functions */
 int /*<<< orphan*/  EBUSY ; 
 int VTCON_MAXPORTS ; 
 int /*<<< orphan*/  errno ; 

__attribute__((used)) static struct pci_vtcon_port *
pci_vtcon_port_add(struct pci_vtcon_softc *sc, const char *name,
    pci_vtcon_cb_t *cb, void *arg)
{
	struct pci_vtcon_port *port;

	if (sc->vsc_nports == VTCON_MAXPORTS) {
		errno = EBUSY;
		return (NULL);
	}

	port = &sc->vsc_ports[sc->vsc_nports++];
	port->vsp_id = sc->vsc_nports - 1;
	port->vsp_sc = sc;
	port->vsp_name = name;
	port->vsp_cb = cb;
	port->vsp_arg = arg;

	if (port->vsp_id == 0) {
		/* port0 */
		port->vsp_txq = 0;
		port->vsp_rxq = 1;
	} else {
		port->vsp_txq = sc->vsc_nports * 2;
		port->vsp_rxq = port->vsp_txq + 1;
	}

	port->vsp_enabled = true;
	return (port);
}