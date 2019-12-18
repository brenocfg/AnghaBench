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
struct vqueue_info {int dummy; } ;
struct pci_vtcon_softc {int dummy; } ;
struct pci_vtcon_port {int /*<<< orphan*/  vsp_arg; int /*<<< orphan*/  (* vsp_cb ) (struct pci_vtcon_port*,int /*<<< orphan*/ ,struct iovec*,int) ;} ;
struct iovec {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 struct pci_vtcon_port* pci_vtcon_vq_to_port (struct pci_vtcon_softc*,struct vqueue_info*) ; 
 int /*<<< orphan*/  stub1 (struct pci_vtcon_port*,int /*<<< orphan*/ ,struct iovec*,int) ; 
 int /*<<< orphan*/  vq_endchains (struct vqueue_info*,int) ; 
 int vq_getchain (struct vqueue_info*,int*,struct iovec*,int,int*) ; 
 scalar_t__ vq_has_descs (struct vqueue_info*) ; 
 int /*<<< orphan*/  vq_relchain (struct vqueue_info*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pci_vtcon_notify_tx(void *vsc, struct vqueue_info *vq)
{
	struct pci_vtcon_softc *sc;
	struct pci_vtcon_port *port;
	struct iovec iov[1];
	uint16_t idx, n;
	uint16_t flags[8];

	sc = vsc;
	port = pci_vtcon_vq_to_port(sc, vq);

	while (vq_has_descs(vq)) {
		n = vq_getchain(vq, &idx, iov, 1, flags);
		assert(n >= 1);
		if (port != NULL)
			port->vsp_cb(port, port->vsp_arg, iov, 1);

		/*
		 * Release this chain and handle more
		 */
		vq_relchain(vq, idx, 0);
	}
	vq_endchains(vq, 1);	/* Generate interrupt if appropriate. */
}