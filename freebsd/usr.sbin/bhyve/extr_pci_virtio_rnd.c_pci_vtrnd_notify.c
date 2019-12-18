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
struct pci_vtrnd_softc {scalar_t__ vrsc_fd; } ;
struct iovec {int /*<<< orphan*/  iov_len; int /*<<< orphan*/  iov_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int read (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vq_endchains (struct vqueue_info*,int) ; 
 int /*<<< orphan*/  vq_getchain (struct vqueue_info*,int /*<<< orphan*/ *,struct iovec*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ vq_has_descs (struct vqueue_info*) ; 
 int /*<<< orphan*/  vq_relchain (struct vqueue_info*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
pci_vtrnd_notify(void *vsc, struct vqueue_info *vq)
{
	struct iovec iov;
	struct pci_vtrnd_softc *sc;
	int len;
	uint16_t idx;

	sc = vsc;

	if (sc->vrsc_fd < 0) {
		vq_endchains(vq, 0);
		return;
	}

	while (vq_has_descs(vq)) {
		vq_getchain(vq, &idx, &iov, 1, NULL);

		len = read(sc->vrsc_fd, iov.iov_base, iov.iov_len);

		DPRINTF(("vtrnd: vtrnd_notify(): %d\r\n", len));

		/* Catastrophe if unable to read from /dev/random */
		assert(len > 0);

		/*
		 * Release this chain and handle more
		 */
		vq_relchain(vq, idx, len);
	}
	vq_endchains(vq, 1);	/* Generate interrupt if appropriate. */
}