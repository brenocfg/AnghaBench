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
struct pci_vtblk_softc {int /*<<< orphan*/  vsc_mtx; int /*<<< orphan*/  vbsc_vq; } ;
struct pci_vtblk_ioreq {int /*<<< orphan*/  io_idx; int /*<<< orphan*/ * io_status; struct pci_vtblk_softc* io_sc; } ;
struct blockif_req {struct pci_vtblk_ioreq* br_param; } ;

/* Variables and functions */
 int ENOSYS ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  VTBLK_S_IOERR ; 
 int /*<<< orphan*/  VTBLK_S_OK ; 
 int /*<<< orphan*/  VTBLK_S_UNSUPP ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vq_endchains (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vq_relchain (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
pci_vtblk_done(struct blockif_req *br, int err)
{
	struct pci_vtblk_ioreq *io = br->br_param;
	struct pci_vtblk_softc *sc = io->io_sc;

	/* convert errno into a virtio block error return */
	if (err == EOPNOTSUPP || err == ENOSYS)
		*io->io_status = VTBLK_S_UNSUPP;
	else if (err != 0)
		*io->io_status = VTBLK_S_IOERR;
	else
		*io->io_status = VTBLK_S_OK;

	/*
	 * Return the descriptor back to the host.
	 * We wrote 1 byte (our status) to host.
	 */
	pthread_mutex_lock(&sc->vsc_mtx);
	vq_relchain(&sc->vbsc_vq, io->io_idx, 1);
	vq_endchains(&sc->vbsc_vq, 0);
	pthread_mutex_unlock(&sc->vsc_mtx);
}