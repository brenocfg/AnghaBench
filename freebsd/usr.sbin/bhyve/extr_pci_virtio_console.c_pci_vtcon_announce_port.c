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
struct pci_vtcon_port {int /*<<< orphan*/ * vsp_name; int /*<<< orphan*/  vsp_sc; int /*<<< orphan*/  vsp_id; } ;
struct pci_vtcon_control {int value; int /*<<< orphan*/  event; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  VTCON_DEVICE_ADD ; 
 int /*<<< orphan*/  VTCON_PORT_NAME ; 
 int /*<<< orphan*/  pci_vtcon_control_send (int /*<<< orphan*/ ,struct pci_vtcon_control*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
pci_vtcon_announce_port(struct pci_vtcon_port *port)
{
	struct pci_vtcon_control event;

	event.id = port->vsp_id;
	event.event = VTCON_DEVICE_ADD;
	event.value = 1;
	pci_vtcon_control_send(port->vsp_sc, &event, NULL, 0);

	event.event = VTCON_PORT_NAME;
	pci_vtcon_control_send(port->vsp_sc, &event, port->vsp_name,
	    strlen(port->vsp_name));
}