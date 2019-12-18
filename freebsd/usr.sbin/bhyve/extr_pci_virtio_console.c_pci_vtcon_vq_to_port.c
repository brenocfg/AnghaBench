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
typedef  int uint16_t ;
struct vqueue_info {int vq_num; } ;
struct pci_vtcon_port {int dummy; } ;
struct pci_vtcon_softc {struct pci_vtcon_port* vsc_ports; struct pci_vtcon_port vsc_control_port; } ;

/* Variables and functions */

__attribute__((used)) static inline struct pci_vtcon_port *
pci_vtcon_vq_to_port(struct pci_vtcon_softc *sc, struct vqueue_info *vq)
{
	uint16_t num = vq->vq_num;

	if (num == 0 || num == 1)
		return (&sc->vsc_ports[0]);

	if (num == 2 || num == 3)
		return (&sc->vsc_control_port);

	return (&sc->vsc_ports[(num / 2) - 1]);
}