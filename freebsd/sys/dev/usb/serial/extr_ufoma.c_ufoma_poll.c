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
struct ufoma_softc {int /*<<< orphan*/  sc_bulk_xfer; int /*<<< orphan*/  sc_ctrl_xfer; } ;
struct ucom_softc {struct ufoma_softc* sc_parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  UFOMA_BULK_ENDPT_MAX ; 
 int /*<<< orphan*/  UFOMA_CTRL_ENDPT_MAX ; 
 int /*<<< orphan*/  usbd_transfer_poll (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ufoma_poll(struct ucom_softc *ucom)
{
	struct ufoma_softc *sc = ucom->sc_parent;
	usbd_transfer_poll(sc->sc_ctrl_xfer, UFOMA_CTRL_ENDPT_MAX);
	usbd_transfer_poll(sc->sc_bulk_xfer, UFOMA_BULK_ENDPT_MAX);
}