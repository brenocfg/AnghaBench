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
struct vqueue_info {int dummy; } ;
struct pci_vtcon_port {int vsp_txq; int vsp_rxq; TYPE_1__* vsp_sc; } ;
struct TYPE_2__ {struct vqueue_info* vsc_queues; } ;

/* Variables and functions */

__attribute__((used)) static inline struct vqueue_info *
pci_vtcon_port_to_vq(struct pci_vtcon_port *port, bool tx_queue)
{
	int qnum;

	qnum = tx_queue ? port->vsp_txq : port->vsp_rxq;
	return (&port->vsp_sc->vsc_queues[qnum]);
}