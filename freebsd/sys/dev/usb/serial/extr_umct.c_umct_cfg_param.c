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
typedef  int uint32_t ;
struct umct_softc {int sc_lcr; } ;
struct ucom_softc {struct umct_softc* sc_parent; } ;
struct termios {int c_cflag; int /*<<< orphan*/  c_ospeed; } ;

/* Variables and functions */
#define  CS5 131 
#define  CS6 130 
#define  CS7 129 
#define  CS8 128 
 int CSIZE ; 
 int CSTOPB ; 
 int PARENB ; 
 int PARODD ; 
 int /*<<< orphan*/  UMCT_SET_BAUD ; 
 int /*<<< orphan*/  UMCT_SET_BAUD_SIZE ; 
 int /*<<< orphan*/  UMCT_SET_LCR ; 
 int /*<<< orphan*/  UMCT_SET_LCR_SIZE ; 
 int umct_calc_baud (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  umct_cfg_do_request (struct umct_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
umct_cfg_param(struct ucom_softc *ucom, struct termios *t)
{
	struct umct_softc *sc = ucom->sc_parent;
	uint32_t value;

	value = umct_calc_baud(t->c_ospeed);
	umct_cfg_do_request(sc, UMCT_SET_BAUD, UMCT_SET_BAUD_SIZE, value);

	value = (sc->sc_lcr & 0x40);

	switch (t->c_cflag & CSIZE) {
	case CS5:
		value |= 0x0;
		break;
	case CS6:
		value |= 0x1;
		break;
	case CS7:
		value |= 0x2;
		break;
	default:
	case CS8:
		value |= 0x3;
		break;
	}

	value |= (t->c_cflag & CSTOPB) ? 0x4 : 0;
	if (t->c_cflag & PARENB) {
		value |= 0x8;
		value |= (t->c_cflag & PARODD) ? 0x0 : 0x10;
	}
	/*
	 * XXX There doesn't seem to be a way to tell the device
	 * to use flow control.
	 */

	sc->sc_lcr = value;
	umct_cfg_do_request(sc, UMCT_SET_LCR, UMCT_SET_LCR_SIZE, value);
}