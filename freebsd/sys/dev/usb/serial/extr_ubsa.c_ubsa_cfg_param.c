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
typedef  int uint16_t ;
struct ucom_softc {struct ubsa_softc* sc_parent; } ;
struct ubsa_softc {int /*<<< orphan*/  sc_ucom; } ;
struct termios {int c_ospeed; int c_cflag; int c_iflag; } ;

/* Variables and functions */
#define  B0 143 
#define  B115200 142 
#define  B1200 141 
#define  B19200 140 
#define  B230400 139 
#define  B2400 138 
#define  B300 137 
#define  B38400 136 
#define  B4800 135 
#define  B57600 134 
#define  B600 133 
#define  B9600 132 
 int CRTSCTS ; 
#define  CS5 131 
#define  CS6 130 
#define  CS7 129 
#define  CS8 128 
 int CSIZE ; 
 int CSTOPB ; 
 int /*<<< orphan*/  DPRINTF (char*,struct ubsa_softc*) ; 
 int IXOFF ; 
 int IXON ; 
 int PARENB ; 
 int PARODD ; 
 int UBSA_FLOW_IRTS ; 
 int UBSA_FLOW_IXON ; 
 int UBSA_FLOW_OCTS ; 
 int UBSA_FLOW_OXON ; 
 int UBSA_PARITY_EVEN ; 
 int UBSA_PARITY_NONE ; 
 int UBSA_PARITY_ODD ; 
 int /*<<< orphan*/  UBSA_REG_BAUDRATE ; 
 int /*<<< orphan*/  UBSA_REG_DATA_BITS ; 
 int /*<<< orphan*/  UBSA_REG_FLOW_CTRL ; 
 int /*<<< orphan*/  UBSA_REG_PARITY ; 
 int /*<<< orphan*/  UBSA_REG_STOP_BITS ; 
 int /*<<< orphan*/  ubsa_cfg_request (struct ubsa_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ubsa_cfg_set_dtr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubsa_cfg_set_rts (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ubsa_cfg_param(struct ucom_softc *ucom, struct termios *t)
{
	struct ubsa_softc *sc = ucom->sc_parent;
	uint16_t value = 0;

	DPRINTF("sc = %p\n", sc);

	switch (t->c_ospeed) {
	case B0:
		ubsa_cfg_request(sc, UBSA_REG_FLOW_CTRL, 0);
		ubsa_cfg_set_dtr(&sc->sc_ucom, 0);
		ubsa_cfg_set_rts(&sc->sc_ucom, 0);
		break;
	case B300:
	case B600:
	case B1200:
	case B2400:
	case B4800:
	case B9600:
	case B19200:
	case B38400:
	case B57600:
	case B115200:
	case B230400:
		value = B230400 / t->c_ospeed;
		ubsa_cfg_request(sc, UBSA_REG_BAUDRATE, value);
		break;
	default:
		return;
	}

	if (t->c_cflag & PARENB)
		value = (t->c_cflag & PARODD) ? UBSA_PARITY_ODD : UBSA_PARITY_EVEN;
	else
		value = UBSA_PARITY_NONE;

	ubsa_cfg_request(sc, UBSA_REG_PARITY, value);

	switch (t->c_cflag & CSIZE) {
	case CS5:
		value = 0;
		break;
	case CS6:
		value = 1;
		break;
	case CS7:
		value = 2;
		break;
	default:
	case CS8:
		value = 3;
		break;
	}

	ubsa_cfg_request(sc, UBSA_REG_DATA_BITS, value);

	value = (t->c_cflag & CSTOPB) ? 1 : 0;

	ubsa_cfg_request(sc, UBSA_REG_STOP_BITS, value);

	value = 0;
	if (t->c_cflag & CRTSCTS)
		value |= UBSA_FLOW_OCTS | UBSA_FLOW_IRTS;

	if (t->c_iflag & (IXON | IXOFF))
		value |= UBSA_FLOW_OXON | UBSA_FLOW_IXON;

	ubsa_cfg_request(sc, UBSA_REG_FLOW_CTRL, value);
}