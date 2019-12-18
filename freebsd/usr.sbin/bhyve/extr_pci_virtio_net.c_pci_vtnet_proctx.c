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
struct vqueue_info {int dummy; } ;
struct pci_vtnet_softc {int /*<<< orphan*/  vsc_be; } ;
struct iovec {int dummy; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int VTNET_MAXSEGS ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ netbe_send (int /*<<< orphan*/ ,struct iovec*,int) ; 
 int vq_getchain (struct vqueue_info*,int /*<<< orphan*/ *,struct iovec*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vq_relchain (struct vqueue_info*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
pci_vtnet_proctx(struct pci_vtnet_softc *sc, struct vqueue_info *vq)
{
	struct iovec iov[VTNET_MAXSEGS + 1];
	uint16_t idx;
	ssize_t len;
	int n;

	/*
	 * Obtain chain of descriptors. The first descriptor also
	 * contains the virtio-net header.
	 */
	n = vq_getchain(vq, &idx, iov, VTNET_MAXSEGS, NULL);
	assert(n >= 1 && n <= VTNET_MAXSEGS);

	len = netbe_send(sc->vsc_be, iov, n);

	/* chain is processed, release it and set len */
	vq_relchain(vq, idx, len > 0 ? len : 0);
}