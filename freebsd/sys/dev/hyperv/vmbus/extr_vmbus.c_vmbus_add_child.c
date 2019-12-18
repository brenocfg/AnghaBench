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
struct vmbus_softc {int /*<<< orphan*/  vmbus_dev; } ;
struct vmbus_channel {int /*<<< orphan*/ * ch_dev; int /*<<< orphan*/  ch_id; struct vmbus_softc* ch_vmbus; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  Giant ; 
 int /*<<< orphan*/ * device_add_child (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_probe_and_attach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_set_ivars (int /*<<< orphan*/ *,struct vmbus_channel*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

int
vmbus_add_child(struct vmbus_channel *chan)
{
	struct vmbus_softc *sc = chan->ch_vmbus;
	device_t parent = sc->vmbus_dev;

	mtx_lock(&Giant);

	chan->ch_dev = device_add_child(parent, NULL, -1);
	if (chan->ch_dev == NULL) {
		mtx_unlock(&Giant);
		device_printf(parent, "device_add_child for chan%u failed\n",
		    chan->ch_id);
		return (ENXIO);
	}
	device_set_ivars(chan->ch_dev, chan);
	device_probe_and_attach(chan->ch_dev);

	mtx_unlock(&Giant);
	return (0);
}