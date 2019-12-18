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
typedef  int /*<<< orphan*/  u_int ;
struct run_softc {int /*<<< orphan*/  sc_mtx; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB_MS_TO_TICKS (int /*<<< orphan*/ ) ; 
 scalar_t__ mtx_owned (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_pause_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
run_delay(struct run_softc *sc, u_int ms)
{
	usb_pause_mtx(mtx_owned(&sc->sc_mtx) ? 
	    &sc->sc_mtx : NULL, USB_MS_TO_TICKS(ms));
}