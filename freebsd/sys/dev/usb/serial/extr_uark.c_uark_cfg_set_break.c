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
typedef  scalar_t__ uint8_t ;
struct ucom_softc {struct uark_softc* sc_parent; } ;
struct uark_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,scalar_t__) ; 
 int /*<<< orphan*/  uark_cfg_write (struct uark_softc*,int,int) ; 

__attribute__((used)) static void
uark_cfg_set_break(struct ucom_softc *ucom, uint8_t onoff)
{
	struct uark_softc *sc = ucom->sc_parent;

	DPRINTF("onoff=%d\n", onoff);

	uark_cfg_write(sc, 4, onoff ? 0x01 : 0x00);
}