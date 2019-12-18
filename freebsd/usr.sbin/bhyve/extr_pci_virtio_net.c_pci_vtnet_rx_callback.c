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
struct pci_vtnet_softc {int /*<<< orphan*/  rx_mtx; } ;
typedef  enum ev_type { ____Placeholder_ev_type } ev_type ;

/* Variables and functions */
 int /*<<< orphan*/  pci_vtnet_rx (struct pci_vtnet_softc*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
pci_vtnet_rx_callback(int fd, enum ev_type type, void *param)
{
	struct pci_vtnet_softc *sc = param;

	pthread_mutex_lock(&sc->rx_mtx);
	pci_vtnet_rx(sc);
	pthread_mutex_unlock(&sc->rx_mtx);

}