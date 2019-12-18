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
struct pci_vtcon_port {int vsp_open; TYPE_1__* vsp_sc; int /*<<< orphan*/  vsp_id; } ;
struct pci_vtcon_control {int value; int /*<<< orphan*/  event; int /*<<< orphan*/  id; } ;
struct TYPE_2__ {int /*<<< orphan*/  vsc_ready; } ;

/* Variables and functions */
 int /*<<< orphan*/  VTCON_PORT_OPEN ; 
 int /*<<< orphan*/  pci_vtcon_control_send (TYPE_1__*,struct pci_vtcon_control*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pci_vtcon_open_port(struct pci_vtcon_port *port, bool open)
{
	struct pci_vtcon_control event;

	if (!port->vsp_sc->vsc_ready) {
		port->vsp_open = true;
		return;
	}

	event.id = port->vsp_id;
	event.event = VTCON_PORT_OPEN;
	event.value = (int)open;
	pci_vtcon_control_send(port->vsp_sc, &event, NULL, 0);
}