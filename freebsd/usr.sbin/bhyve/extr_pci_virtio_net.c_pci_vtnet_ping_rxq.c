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
struct pci_vtnet_softc {int /*<<< orphan*/  rx_mtx; int /*<<< orphan*/  vsc_be; } ;

/* Variables and functions */
 int /*<<< orphan*/  netbe_rx_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vq_kick_disable (struct vqueue_info*) ; 

__attribute__((used)) static void
pci_vtnet_ping_rxq(void *vsc, struct vqueue_info *vq)
{
	struct pci_vtnet_softc *sc = vsc;

	/*
	 * A qnotify means that the rx process can now begin.
	 */
	pthread_mutex_lock(&sc->rx_mtx);
	vq_kick_disable(vq);
	netbe_rx_enable(sc->vsc_be);
	pthread_mutex_unlock(&sc->rx_mtx);
}