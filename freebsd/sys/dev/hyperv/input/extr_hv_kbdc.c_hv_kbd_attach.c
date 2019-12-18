#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * hs_xact_ctx; int /*<<< orphan*/  dev; int /*<<< orphan*/  hs_chan; } ;
typedef  TYPE_1__ hv_kbd_sc ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  HV_KBD_PROTO_REQ_SZ ; 
 int /*<<< orphan*/  HV_KBD_PROTO_RESP_SZ ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 TYPE_1__* device_get_softc (int /*<<< orphan*/ ) ; 
 int hv_kbd_attach1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int hv_kbd_connect_vsp (TYPE_1__*) ; 
 int /*<<< orphan*/  hv_kbd_detach (int /*<<< orphan*/ ) ; 
 int hv_kbd_drv_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hv_kbd_init (TYPE_1__*) ; 
 int /*<<< orphan*/  hv_kbd_read_channel ; 
 int /*<<< orphan*/  hv_kbd_sysctl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmbus_get_channel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * vmbus_xact_ctx_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
hv_kbd_attach(device_t dev)
{
	int error = 0;
	hv_kbd_sc *sc;

	sc = device_get_softc(dev);
	sc->hs_chan = vmbus_get_channel(dev);
	sc->dev = dev;
	hv_kbd_init(sc);
	sc->hs_xact_ctx = vmbus_xact_ctx_create(bus_get_dma_tag(dev),
	    HV_KBD_PROTO_REQ_SZ, HV_KBD_PROTO_RESP_SZ, 0);
	if (sc->hs_xact_ctx == NULL) {
		error = ENOMEM;
		goto failed;
	}

	error = hv_kbd_attach1(dev, hv_kbd_read_channel);
	if (error)
		goto failed;
	error = hv_kbd_connect_vsp(sc);
	if (error)
		goto failed;

	error = hv_kbd_drv_attach(dev);
	if (error)
		goto failed;
	hv_kbd_sysctl(dev);
	return (0);
failed:
	hv_kbd_detach(dev);
	return (error);
}