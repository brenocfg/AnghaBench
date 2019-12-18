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
typedef  scalar_t__ uint8_t ;
struct musbotg_td {int ep_no; scalar_t__ max_frame_size; } ;
struct musbotg_softc {scalar_t__ sc_mode; int sc_channel_mask; int sc_ep_max; TYPE_1__* sc_hw_ep_profile; } ;
struct TYPE_2__ {scalar_t__ max_in_frame_size; scalar_t__ max_out_frame_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTFN (int,char*,int) ; 
 scalar_t__ MUSB2_DEVICE_MODE ; 
 int /*<<< orphan*/  musbotg_ep_int_set (struct musbotg_softc*,int,int) ; 

__attribute__((used)) static int
musbotg_channel_alloc(struct musbotg_softc *sc, struct musbotg_td *td, uint8_t is_tx)
{
	int ch;
	int ep;

	ep = td->ep_no;

	/* In device mode each EP got its own channel */
	if (sc->sc_mode == MUSB2_DEVICE_MODE) {
		musbotg_ep_int_set(sc, ep, 1);
		return (ep);
	}

	/*
	 * All control transactions go through EP0
	 */
	if (ep == 0) {
		if (sc->sc_channel_mask & (1 << 0))
			return (-1);
		sc->sc_channel_mask |= (1 << 0);
		musbotg_ep_int_set(sc, ep, 1);
		return (0);
	}

	for (ch = sc->sc_ep_max; ch != 0; ch--) {
		if (sc->sc_channel_mask & (1 << ch))
			continue;

		/* check FIFO size requirement */
		if (is_tx) {
			if (td->max_frame_size >
			    sc->sc_hw_ep_profile[ch].max_in_frame_size)
				continue;
		} else {
			if (td->max_frame_size >
			    sc->sc_hw_ep_profile[ch].max_out_frame_size)
				continue;
		}
		sc->sc_channel_mask |= (1 << ch);
		musbotg_ep_int_set(sc, ch, 1);
		return (ch);
	}

	DPRINTFN(-1, "No available channels. Mask: %04x\n",  sc->sc_channel_mask);

	return (-1);
}