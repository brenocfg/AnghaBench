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
struct TYPE_2__ {int /*<<< orphan*/ * rb_rxdesc; int /*<<< orphan*/  rb_rxd; } ;
struct hme_softc {int sc_flags; TYPE_1__ sc_rb; } ;

/* Variables and functions */
 int /*<<< orphan*/  HME_DESC_RXLEN (struct hme_softc*,int /*<<< orphan*/ *) ; 
 int HME_PCI ; 
 int HME_XD_ENCODE_RSIZE (int /*<<< orphan*/ ) ; 
 int HME_XD_OWN ; 
 int /*<<< orphan*/  HME_XD_SETFLAGS (int,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static __inline void
hme_discard_rxbuf(struct hme_softc *sc, int ix)
{

	/*
	 * Dropped a packet, reinitialize the descriptor and turn the
	 * ownership back to the hardware.
	 */
	HME_XD_SETFLAGS(sc->sc_flags & HME_PCI, sc->sc_rb.rb_rxd,
	    ix, HME_XD_OWN | HME_XD_ENCODE_RSIZE(HME_DESC_RXLEN(sc,
	    &sc->sc_rb.rb_rxdesc[ix])));
}