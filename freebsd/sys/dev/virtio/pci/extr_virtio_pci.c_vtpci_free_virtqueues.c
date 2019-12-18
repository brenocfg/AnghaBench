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
struct vtpci_virtqueue {int /*<<< orphan*/ * vtv_vq; } ;
struct vtpci_softc {int vtpci_nvqs; struct vtpci_virtqueue* vtpci_vqs; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  VIRTIO_PCI_QUEUE_PFN ; 
 int /*<<< orphan*/  free (struct vtpci_virtqueue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virtqueue_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vtpci_select_virtqueue (struct vtpci_softc*,int) ; 
 int /*<<< orphan*/  vtpci_write_config_4 (struct vtpci_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vtpci_free_virtqueues(struct vtpci_softc *sc)
{
	struct vtpci_virtqueue *vqx;
	int idx;

	for (idx = 0; idx < sc->vtpci_nvqs; idx++) {
		vqx = &sc->vtpci_vqs[idx];

		vtpci_select_virtqueue(sc, idx);
		vtpci_write_config_4(sc, VIRTIO_PCI_QUEUE_PFN, 0);

		virtqueue_free(vqx->vtv_vq);
		vqx->vtv_vq = NULL;
	}

	free(sc->vtpci_vqs, M_DEVBUF);
	sc->vtpci_vqs = NULL;
	sc->vtpci_nvqs = 0;
}