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
struct vtmmio_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  scalar_t__ bus_size_t ;

/* Variables and functions */
 scalar_t__ VIRTIO_MMIO_CONFIG ; 
 struct vtmmio_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vtmmio_write_config_1 (struct vtmmio_softc*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vtmmio_write_config_2 (struct vtmmio_softc*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vtmmio_write_config_4 (struct vtmmio_softc*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vtmmio_write_dev_config(device_t dev, bus_size_t offset,
    void *src, int length)
{
	struct vtmmio_softc *sc;
	bus_size_t off;
	uint8_t *s;
	int size;

	sc = device_get_softc(dev);
	off = VIRTIO_MMIO_CONFIG + offset;

	for (s = src; length > 0; s += size, off += size, length -= size) {
#ifdef ALLOW_WORD_ALIGNED_ACCESS
		if (length >= 4) {
			size = 4;
			vtmmio_write_config_4(sc, off, *(uint32_t *)s);
		} else if (length >= 2) {
			size = 2;
			vtmmio_write_config_2(sc, off, *(uint16_t *)s);
		} else
#endif
		{
			size = 1;
			vtmmio_write_config_1(sc, off, *s);
		}
	}
}