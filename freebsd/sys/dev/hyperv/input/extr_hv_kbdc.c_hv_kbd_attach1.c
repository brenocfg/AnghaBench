#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vmbus_chan_callback_t ;
struct TYPE_4__ {int /*<<< orphan*/  buf; int /*<<< orphan*/  hs_chan; int /*<<< orphan*/  buflen; } ;
typedef  TYPE_1__ hv_kbd_sc ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  HV_BUFF_SIZE ; 
 int /*<<< orphan*/  HV_KBD_RINGBUFF_RECV_SZ ; 
 int /*<<< orphan*/  HV_KBD_RINGBUFF_SEND_SZ ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 TYPE_1__* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  malloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int vmbus_chan_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  vmbus_chan_set_readbatch (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
hv_kbd_attach1(device_t dev, vmbus_chan_callback_t cb)
{
	int ret;
	hv_kbd_sc *sc;

        sc = device_get_softc(dev);
	sc->buflen = HV_BUFF_SIZE;
	sc->buf = malloc(sc->buflen, M_DEVBUF, M_WAITOK | M_ZERO);
	vmbus_chan_set_readbatch(sc->hs_chan, false);
	ret = vmbus_chan_open(
		sc->hs_chan,
		HV_KBD_RINGBUFF_SEND_SZ,
		HV_KBD_RINGBUFF_RECV_SZ,
		NULL, 0,
		cb,
		sc);
	if (ret != 0) {
		free(sc->buf, M_DEVBUF);
	}
	return (ret);
}