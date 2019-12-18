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
struct vmbus_softc {int /*<<< orphan*/  vmbus_dev; int /*<<< orphan*/  vmbus_scandone; void* vmbus_subchtq; int /*<<< orphan*/  vmbus_scandone_task; void* vmbus_devtq; } ;

/* Variables and functions */
 int /*<<< orphan*/  GIANT_REQUIRED ; 
 int /*<<< orphan*/  Giant ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  PI_NET ; 
 int /*<<< orphan*/  TASK_INIT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vmbus_softc*) ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  bus_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_generic_probe (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  mtx_sleep (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 void* taskqueue_create (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  taskqueue_start_threads (void**,int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  taskqueue_thread_enqueue ; 
 int vmbus_req_channels (struct vmbus_softc*) ; 
 int /*<<< orphan*/  vmbus_scan_done_task ; 

__attribute__((used)) static int
vmbus_scan(struct vmbus_softc *sc)
{
	int error;

	/*
	 * Identify, probe and attach for non-channel devices.
	 */
	bus_generic_probe(sc->vmbus_dev);
	bus_generic_attach(sc->vmbus_dev);

	/*
	 * This taskqueue serializes vmbus devices' attach and detach
	 * for channel offer and rescind messages.
	 */
	sc->vmbus_devtq = taskqueue_create("vmbus dev", M_WAITOK,
	    taskqueue_thread_enqueue, &sc->vmbus_devtq);
	taskqueue_start_threads(&sc->vmbus_devtq, 1, PI_NET, "vmbusdev");
	TASK_INIT(&sc->vmbus_scandone_task, 0, vmbus_scan_done_task, sc);

	/*
	 * This taskqueue handles sub-channel detach, so that vmbus
	 * device's detach running in vmbus_devtq can drain its sub-
	 * channels.
	 */
	sc->vmbus_subchtq = taskqueue_create("vmbus subch", M_WAITOK,
	    taskqueue_thread_enqueue, &sc->vmbus_subchtq);
	taskqueue_start_threads(&sc->vmbus_subchtq, 1, PI_NET, "vmbussch");

	/*
	 * Start vmbus scanning.
	 */
	error = vmbus_req_channels(sc);
	if (error) {
		device_printf(sc->vmbus_dev, "channel request failed: %d\n",
		    error);
		return (error);
	}

	/*
	 * Wait for all vmbus devices from the initial channel offers to be
	 * attached.
	 */
	GIANT_REQUIRED;
	while (!sc->vmbus_scandone)
		mtx_sleep(&sc->vmbus_scandone, &Giant, 0, "vmbusdev", 0);

	if (bootverbose) {
		device_printf(sc->vmbus_dev, "device scan, probe and attach "
		    "done\n");
	}
	return (0);
}