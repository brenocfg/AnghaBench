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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct vtpci_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  scalar_t__ bus_size_t ;

/* Variables and functions */
 scalar_t__ VIRTIO_PCI_CONFIG (struct vtpci_softc*) ; 
 struct vtpci_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vtpci_read_config_1 (struct vtpci_softc*,scalar_t__) ; 
 int /*<<< orphan*/  vtpci_read_config_2 (struct vtpci_softc*,scalar_t__) ; 
 int /*<<< orphan*/  vtpci_read_config_4 (struct vtpci_softc*,scalar_t__) ; 

__attribute__((used)) static void
vtpci_read_dev_config(device_t dev, bus_size_t offset,
    void *dst, int length)
{
	struct vtpci_softc *sc;
	bus_size_t off;
	uint8_t *d;
	int size;

	sc = device_get_softc(dev);
	off = VIRTIO_PCI_CONFIG(sc) + offset;

	for (d = dst; length > 0; d += size, off += size, length -= size) {
		if (length >= 4) {
			size = 4;
			*(uint32_t *)d = vtpci_read_config_4(sc, off);
		} else if (length >= 2) {
			size = 2;
			*(uint16_t *)d = vtpci_read_config_2(sc, off);
		} else {
			size = 1;
			*d = vtpci_read_config_1(sc, off);
		}
	}
}