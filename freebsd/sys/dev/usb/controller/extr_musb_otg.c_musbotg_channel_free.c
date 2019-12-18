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
struct musbotg_td {int channel; } ;
struct musbotg_softc {scalar_t__ sc_mode; int sc_channel_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTFN (int,char*,int) ; 
 scalar_t__ MUSB2_DEVICE_MODE ; 
 int /*<<< orphan*/  musbotg_ep_int_set (struct musbotg_softc*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void	
musbotg_channel_free(struct musbotg_softc *sc, struct musbotg_td *td)
{

	DPRINTFN(1, "ep_no=%d\n", td->channel);

	if (sc->sc_mode == MUSB2_DEVICE_MODE)
		return;

	if (td == NULL)
		return;
	if (td->channel == -1)
		return;

	musbotg_ep_int_set(sc, td->channel, 0);
	sc->sc_channel_mask &= ~(1 << td->channel);

	td->channel = -1;
}