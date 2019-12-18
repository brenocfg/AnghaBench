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
struct vtpci_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VIRTIO_PCI_QUEUE_SEL ; 
 int /*<<< orphan*/  vtpci_write_config_2 (struct vtpci_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
vtpci_select_virtqueue(struct vtpci_softc *sc, int idx)
{

	vtpci_write_config_2(sc, VIRTIO_PCI_QUEUE_SEL, idx);
}