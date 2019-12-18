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
struct vtnet_softc {int /*<<< orphan*/  vtnet_ifp; int /*<<< orphan*/  vtnet_tick_ch; int /*<<< orphan*/  vtnet_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  INTR_TYPE_NET ; 
 int /*<<< orphan*/  VTNET_CORE_LOCK_INIT (struct vtnet_softc*) ; 
 int /*<<< orphan*/  VTNET_CORE_MTX (struct vtnet_softc*) ; 
 int /*<<< orphan*/  callout_init_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct vtnet_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ether_ifdetach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virtio_set_feature_desc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int virtio_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int vtnet_alloc_rx_filters (struct vtnet_softc*) ; 
 int vtnet_alloc_rxtx_queues (struct vtnet_softc*) ; 
 int vtnet_alloc_virtqueues (struct vtnet_softc*) ; 
 int /*<<< orphan*/  vtnet_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vtnet_feature_desc ; 
 int /*<<< orphan*/  vtnet_netmap_attach (struct vtnet_softc*) ; 
 int /*<<< orphan*/  vtnet_setup_features (struct vtnet_softc*) ; 
 int vtnet_setup_interface (struct vtnet_softc*) ; 
 int /*<<< orphan*/  vtnet_setup_sysctl (struct vtnet_softc*) ; 
 int /*<<< orphan*/  vtnet_start_taskqueues (struct vtnet_softc*) ; 

__attribute__((used)) static int
vtnet_attach(device_t dev)
{
	struct vtnet_softc *sc;
	int error;

	sc = device_get_softc(dev);
	sc->vtnet_dev = dev;

	/* Register our feature descriptions. */
	virtio_set_feature_desc(dev, vtnet_feature_desc);

	VTNET_CORE_LOCK_INIT(sc);
	callout_init_mtx(&sc->vtnet_tick_ch, VTNET_CORE_MTX(sc), 0);

	vtnet_setup_sysctl(sc);
	vtnet_setup_features(sc);

	error = vtnet_alloc_rx_filters(sc);
	if (error) {
		device_printf(dev, "cannot allocate Rx filters\n");
		goto fail;
	}

	error = vtnet_alloc_rxtx_queues(sc);
	if (error) {
		device_printf(dev, "cannot allocate queues\n");
		goto fail;
	}

	error = vtnet_alloc_virtqueues(sc);
	if (error) {
		device_printf(dev, "cannot allocate virtqueues\n");
		goto fail;
	}

	error = vtnet_setup_interface(sc);
	if (error) {
		device_printf(dev, "cannot setup interface\n");
		goto fail;
	}

	error = virtio_setup_intr(dev, INTR_TYPE_NET);
	if (error) {
		device_printf(dev, "cannot setup virtqueue interrupts\n");
		/* BMV: This will crash if during boot! */
		ether_ifdetach(sc->vtnet_ifp);
		goto fail;
	}

#ifdef DEV_NETMAP
	vtnet_netmap_attach(sc);
#endif /* DEV_NETMAP */

	vtnet_start_taskqueues(sc);

fail:
	if (error)
		vtnet_detach(dev);

	return (error);
}