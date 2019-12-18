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
struct uplcom_softc {int sc_chiptype; } ;
struct ucom_softc {struct uplcom_softc* sc_parent; } ;
struct termios {int c_ospeed; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,...) ; 
 int EIO ; 
#define  TYPE_PL2303HX 129 
#define  TYPE_PL2303HXD 128 
 int /*<<< orphan*/  uplcom_baud_supported (int) ; 

__attribute__((used)) static int
uplcom_pre_param(struct ucom_softc *ucom, struct termios *t)
{
	struct uplcom_softc *sc = ucom->sc_parent;

	DPRINTF("\n");

	/**
	 * Check requested baud rate.
	 *
	 * The PL2303 can only set specific baud rates, up to 1228800 baud.
	 * The PL2303HX can set any baud rate up to 6Mb.
	 * The PL2303HX rev. D can set any baud rate up to 12Mb.
	 *
	 */

	/* accept raw divisor data, if someone wants to do the math in user domain */
	if (t->c_ospeed & 0x80000000)
		return 0;
	switch (sc->sc_chiptype) {
		case TYPE_PL2303HXD:
			if (t->c_ospeed <= 12000000)
				return (0);
			break;
		case TYPE_PL2303HX:
			if (t->c_ospeed <= 6000000)
				return (0);
			break;
		default:
			if (uplcom_baud_supported(t->c_ospeed))
				return (0);
			break;
	}

	DPRINTF("uplcom_param: bad baud rate (%d)\n", t->c_ospeed);
	return (EIO);
}