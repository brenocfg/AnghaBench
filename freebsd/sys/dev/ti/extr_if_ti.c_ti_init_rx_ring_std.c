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
struct ti_softc {int ti_std; } ;
struct ti_cmd_desc {int dummy; } ;

/* Variables and functions */
 int ENOBUFS ; 
 int TI_STD_RX_RING_CNT ; 
 int /*<<< orphan*/  TI_UPDATE_STDPROD (struct ti_softc*,int) ; 
 scalar_t__ ti_newbuf_std (struct ti_softc*,int) ; 

__attribute__((used)) static int
ti_init_rx_ring_std(struct ti_softc *sc)
{
	int i;
	struct ti_cmd_desc cmd;

	for (i = 0; i < TI_STD_RX_RING_CNT; i++) {
		if (ti_newbuf_std(sc, i) != 0)
			return (ENOBUFS);
	}

	sc->ti_std = TI_STD_RX_RING_CNT - 1;
	TI_UPDATE_STDPROD(sc, TI_STD_RX_RING_CNT - 1);

	return (0);
}