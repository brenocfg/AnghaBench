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
typedef  int /*<<< orphan*/  uint64_t ;
struct vtmmio_softc {int vtmmio_nvqs; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  VIRTIO_CONFIG_STATUS_ACK ; 
 int /*<<< orphan*/  VIRTIO_CONFIG_STATUS_DRIVER ; 
 scalar_t__ VIRTIO_CONFIG_STATUS_RESET ; 
 int /*<<< orphan*/  VIRTIO_MMIO_GUEST_PAGE_SIZE ; 
 struct vtmmio_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ vtmmio_get_status (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vtmmio_negotiate_features (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int vtmmio_reinit_virtqueue (struct vtmmio_softc*,int) ; 
 int /*<<< orphan*/  vtmmio_set_status (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vtmmio_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vtmmio_write_config_4 (struct vtmmio_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
vtmmio_reinit(device_t dev, uint64_t features)
{
	struct vtmmio_softc *sc;
	int idx, error;

	sc = device_get_softc(dev);

	if (vtmmio_get_status(dev) != VIRTIO_CONFIG_STATUS_RESET)
		vtmmio_stop(dev);

	/*
	 * Quickly drive the status through ACK and DRIVER. The device
	 * does not become usable again until vtmmio_reinit_complete().
	 */
	vtmmio_set_status(dev, VIRTIO_CONFIG_STATUS_ACK);
	vtmmio_set_status(dev, VIRTIO_CONFIG_STATUS_DRIVER);

	vtmmio_negotiate_features(dev, features);

	vtmmio_write_config_4(sc, VIRTIO_MMIO_GUEST_PAGE_SIZE,
	    (1 << PAGE_SHIFT));

	for (idx = 0; idx < sc->vtmmio_nvqs; idx++) {
		error = vtmmio_reinit_virtqueue(sc, idx);
		if (error)
			return (error);
	}

	return (0);
}