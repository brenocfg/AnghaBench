#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct umidi_chan {int /*<<< orphan*/  mtx; int /*<<< orphan*/ * xfer; TYPE_1__* sub; } ;
struct uaudio_softc {struct umidi_chan sc_midi_chan; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int /*<<< orphan*/  fifo; } ;

/* Variables and functions */
 size_t UMIDI_EMB_JACK_MAX ; 
 int /*<<< orphan*/  UMIDI_N_TRANSFER ; 
 size_t UMIDI_RX_TRANSFER ; 
 struct uaudio_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_fifo_detach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbd_transfer_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_transfer_unsetup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
umidi_detach(device_t dev)
{
	struct uaudio_softc *sc = device_get_softc(dev);
	struct umidi_chan *chan = &sc->sc_midi_chan;
	uint32_t n;

	for (n = 0; n < UMIDI_EMB_JACK_MAX; n++)
		usb_fifo_detach(&chan->sub[n].fifo);

	mtx_lock(&chan->mtx);

	usbd_transfer_stop(chan->xfer[UMIDI_RX_TRANSFER]);

	mtx_unlock(&chan->mtx);

	usbd_transfer_unsetup(chan->xfer, UMIDI_N_TRANSFER);

	mtx_destroy(&chan->mtx);

	return (0);
}