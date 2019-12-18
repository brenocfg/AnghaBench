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
typedef  int /*<<< orphan*/  usb_error_t ;
typedef  int /*<<< orphan*/  uint8_t ;
struct urtw_softc {int /*<<< orphan*/  sc_mtx; } ;

/* Variables and functions */
 int /*<<< orphan*/  URTW_TX_ANTENNA ; 
 int /*<<< orphan*/  urtw_write8_m (struct urtw_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_pause_mtx (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static usb_error_t
urtw_8185_tx_antenna(struct urtw_softc *sc, uint8_t ant)
{
	usb_error_t error;

	urtw_write8_m(sc, URTW_TX_ANTENNA, ant);
	usb_pause_mtx(&sc->sc_mtx, 1);
fail:
	return (error);
}