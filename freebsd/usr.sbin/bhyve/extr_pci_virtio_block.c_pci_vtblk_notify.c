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
struct pci_vtblk_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_vtblk_proc (struct pci_vtblk_softc*,struct vqueue_info*) ; 
 scalar_t__ vq_has_descs (struct vqueue_info*) ; 

__attribute__((used)) static void
pci_vtblk_notify(void *vsc, struct vqueue_info *vq)
{
	struct pci_vtblk_softc *sc = vsc;

	while (vq_has_descs(vq))
		pci_vtblk_proc(sc, vq);
}