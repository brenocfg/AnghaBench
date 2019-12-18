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
typedef  int /*<<< orphan*/  uint8_t ;
struct ucom_super_softc {int /*<<< orphan*/  sc_tq; } ;
struct ucom_softc {struct ucom_super_softc* sc_super; } ;

/* Variables and functions */
 int /*<<< orphan*/  usb_proc_is_gone (int /*<<< orphan*/ *) ; 

uint8_t
ucom_cfg_is_gone(struct ucom_softc *sc)
{
	struct ucom_super_softc *ssc = sc->sc_super;

	return (usb_proc_is_gone(&ssc->sc_tq));
}