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
struct vqueue_info {int dummy; } ;
struct pci_vtnet_softc {int tx_in_progress; int /*<<< orphan*/  tx_mtx; int /*<<< orphan*/  tx_cond; scalar_t__ resetting; struct vqueue_info* vsc_queues; } ;

/* Variables and functions */
 size_t VTNET_TXQ ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  pci_vtnet_proctx (struct pci_vtnet_softc*,struct vqueue_info*) ; 
 int pthread_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vq_endchains (struct vqueue_info*,int) ; 
 scalar_t__ vq_has_descs (struct vqueue_info*) ; 
 int /*<<< orphan*/  vq_kick_disable (struct vqueue_info*) ; 
 int /*<<< orphan*/  vq_kick_enable (struct vqueue_info*) ; 

__attribute__((used)) static void *
pci_vtnet_tx_thread(void *param)
{
	struct pci_vtnet_softc *sc = param;
	struct vqueue_info *vq;
	int error;

	vq = &sc->vsc_queues[VTNET_TXQ];

	/*
	 * Let us wait till the tx queue pointers get initialised &
	 * first tx signaled
	 */
	pthread_mutex_lock(&sc->tx_mtx);
	error = pthread_cond_wait(&sc->tx_cond, &sc->tx_mtx);
	assert(error == 0);

	for (;;) {
		/* note - tx mutex is locked here */
		while (sc->resetting || !vq_has_descs(vq)) {
			vq_kick_enable(vq);
			if (!sc->resetting && vq_has_descs(vq))
				break;

			sc->tx_in_progress = 0;
			error = pthread_cond_wait(&sc->tx_cond, &sc->tx_mtx);
			assert(error == 0);
		}
		vq_kick_disable(vq);
		sc->tx_in_progress = 1;
		pthread_mutex_unlock(&sc->tx_mtx);

		do {
			/*
			 * Run through entries, placing them into
			 * iovecs and sending when an end-of-packet
			 * is found
			 */
			pci_vtnet_proctx(sc, vq);
		} while (vq_has_descs(vq));

		/*
		 * Generate an interrupt if needed.
		 */
		vq_endchains(vq, /*used_all_avail=*/1);

		pthread_mutex_lock(&sc->tx_mtx);
	}
}