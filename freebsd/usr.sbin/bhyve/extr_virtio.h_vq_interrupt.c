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
struct vqueue_info {int /*<<< orphan*/  vq_msix_idx; } ;
struct virtio_softc {int /*<<< orphan*/  vs_pi; int /*<<< orphan*/  vs_isr; } ;

/* Variables and functions */
 int /*<<< orphan*/  VS_LOCK (struct virtio_softc*) ; 
 int /*<<< orphan*/  VS_UNLOCK (struct virtio_softc*) ; 
 int /*<<< orphan*/  VTCFG_ISR_QUEUES ; 
 int /*<<< orphan*/  pci_generate_msi (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_generate_msix (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_lintr_assert (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_msix_enabled (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
vq_interrupt(struct virtio_softc *vs, struct vqueue_info *vq)
{

	if (pci_msix_enabled(vs->vs_pi))
		pci_generate_msix(vs->vs_pi, vq->vq_msix_idx);
	else {
		VS_LOCK(vs);
		vs->vs_isr |= VTCFG_ISR_QUEUES;
		pci_generate_msi(vs->vs_pi, 0);
		pci_lintr_assert(vs->vs_pi);
		VS_UNLOCK(vs);
	}
}