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
typedef  scalar_t__ usb_error_t ;
struct urtw_softc {int /*<<< orphan*/  sc_mtx; } ;

/* Variables and functions */
 int /*<<< orphan*/  URTW_8225_ADDR_7_MAGIC ; 
 int /*<<< orphan*/ * urtw_8225_channel ; 
 int /*<<< orphan*/  urtw_8225_write (struct urtw_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ urtw_8225v2b_set_txpwrlvl (struct urtw_softc*,int) ; 
 int /*<<< orphan*/  usb_pause_mtx (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static usb_error_t
urtw_8225v2b_rf_set_chan(struct urtw_softc *sc, int chan)
{
	usb_error_t error;

	error = urtw_8225v2b_set_txpwrlvl(sc, chan);
	if (error)
		goto fail;

	urtw_8225_write(sc, URTW_8225_ADDR_7_MAGIC, urtw_8225_channel[chan]);
	usb_pause_mtx(&sc->sc_mtx, 10);
fail:
	return (error);
}