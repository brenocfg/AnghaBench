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
struct pci_vtscsi_softc {int dummy; } ;
struct iovec {int dummy; } ;

/* Variables and functions */
 int VTSCSI_MAXSEG ; 
 int /*<<< orphan*/  buf_to_iov (void*,int,struct iovec*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  free (void*) ; 
 size_t iov_to_buf (struct iovec*,int /*<<< orphan*/ ,void**) ; 
 int pci_vtscsi_control_handle (struct pci_vtscsi_softc*,void*,size_t) ; 
 int /*<<< orphan*/  vq_endchains (struct vqueue_info*,int) ; 
 int /*<<< orphan*/  vq_getchain (struct vqueue_info*,int /*<<< orphan*/ *,struct iovec*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ vq_has_descs (struct vqueue_info*) ; 
 int /*<<< orphan*/  vq_relchain (struct vqueue_info*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
pci_vtscsi_controlq_notify(void *vsc, struct vqueue_info *vq)
{
	struct pci_vtscsi_softc *sc;
	struct iovec iov[VTSCSI_MAXSEG];
	uint16_t idx, n;
	void *buf = NULL;
	size_t bufsize;
	int iolen;

	sc = vsc;

	while (vq_has_descs(vq)) {
		n = vq_getchain(vq, &idx, iov, VTSCSI_MAXSEG, NULL);
		bufsize = iov_to_buf(iov, n, &buf);
		iolen = pci_vtscsi_control_handle(sc, buf, bufsize);
		buf_to_iov(buf + bufsize - iolen, iolen, iov, n,
		    bufsize - iolen);

		/*
		 * Release this chain and handle more
		 */
		vq_relchain(vq, idx, iolen);
	}
	vq_endchains(vq, 1);	/* Generate interrupt if appropriate. */
	free(buf);
}