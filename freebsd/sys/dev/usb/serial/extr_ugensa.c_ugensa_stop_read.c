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
struct ugensa_sub_softc {int /*<<< orphan*/ * sc_xfer; } ;
struct ugensa_softc {struct ugensa_sub_softc* sc_sub; } ;
struct ucom_softc {int sc_portno; struct ugensa_softc* sc_parent; } ;

/* Variables and functions */
 size_t UGENSA_BULK_DT_RD ; 
 int /*<<< orphan*/  usbd_transfer_stop (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ugensa_stop_read(struct ucom_softc *ucom)
{
	struct ugensa_softc *sc = ucom->sc_parent;
	struct ugensa_sub_softc *ssc = sc->sc_sub + ucom->sc_portno;

	usbd_transfer_stop(ssc->sc_xfer[UGENSA_BULK_DT_RD]);
}