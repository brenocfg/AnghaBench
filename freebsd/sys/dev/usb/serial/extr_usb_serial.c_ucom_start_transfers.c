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
struct ucom_softc {int sc_flag; TYPE_1__* sc_callback; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* ucom_start_write ) (struct ucom_softc*) ;int /*<<< orphan*/  (* ucom_start_read ) (struct ucom_softc*) ;} ;

/* Variables and functions */
 int UCOM_FLAG_HL_READY ; 
 int /*<<< orphan*/  stub1 (struct ucom_softc*) ; 
 int /*<<< orphan*/  stub2 (struct ucom_softc*) ; 

__attribute__((used)) static void
ucom_start_transfers(struct ucom_softc *sc)
{
	if (!(sc->sc_flag & UCOM_FLAG_HL_READY)) {
		return;
	}
	/*
	 * Make sure that data transfers are started in both
	 * directions:
	 */
	if (sc->sc_callback->ucom_start_read) {
		(sc->sc_callback->ucom_start_read) (sc);
	}
	if (sc->sc_callback->ucom_start_write) {
		(sc->sc_callback->ucom_start_write) (sc);
	}
}