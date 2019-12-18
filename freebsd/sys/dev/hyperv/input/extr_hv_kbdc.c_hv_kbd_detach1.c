#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  buf; } ;
typedef  TYPE_1__ hv_kbd_sc ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 TYPE_1__* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmbus_chan_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmbus_get_channel (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
hv_kbd_detach1(device_t dev)
{
	hv_kbd_sc *sc = device_get_softc(dev);
	vmbus_chan_close(vmbus_get_channel(dev));
	free(sc->buf, M_DEVBUF);
	return (0);
}