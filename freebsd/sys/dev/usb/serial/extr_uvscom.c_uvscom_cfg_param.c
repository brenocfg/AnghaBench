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
typedef  int /*<<< orphan*/  uint16_t ;
struct uvscom_softc {int dummy; } ;
struct ucom_softc {struct uvscom_softc* sc_parent; } ;
struct termios {int c_ospeed; int c_cflag; } ;

/* Variables and functions */
#define  B115200 142 
#define  B1200 141 
#define  B150 140 
#define  B19200 139 
#define  B2400 138 
#define  B300 137 
#define  B38400 136 
#define  B4800 135 
#define  B57600 134 
#define  B600 133 
#define  B9600 132 
#define  CS5 131 
#define  CS6 130 
#define  CS7 129 
#define  CS8 128 
 int CSIZE ; 
 int CSTOPB ; 
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int PARENB ; 
 int PARODD ; 
 int /*<<< orphan*/  UVSCOM_DATA_BIT_5 ; 
 int /*<<< orphan*/  UVSCOM_DATA_BIT_6 ; 
 int /*<<< orphan*/  UVSCOM_DATA_BIT_7 ; 
 int /*<<< orphan*/  UVSCOM_DATA_BIT_8 ; 
 int /*<<< orphan*/  UVSCOM_PARITY_EVEN ; 
 int /*<<< orphan*/  UVSCOM_PARITY_NONE ; 
 int /*<<< orphan*/  UVSCOM_PARITY_ODD ; 
 int /*<<< orphan*/  UVSCOM_SET_PARAM ; 
 int /*<<< orphan*/  UVSCOM_SET_SPEED ; 
 int /*<<< orphan*/  UVSCOM_SPEED_115200BPS ; 
 int /*<<< orphan*/  UVSCOM_SPEED_1200BPS ; 
 int /*<<< orphan*/  UVSCOM_SPEED_150BPS ; 
 int /*<<< orphan*/  UVSCOM_SPEED_19200BPS ; 
 int /*<<< orphan*/  UVSCOM_SPEED_2400BPS ; 
 int /*<<< orphan*/  UVSCOM_SPEED_300BPS ; 
 int /*<<< orphan*/  UVSCOM_SPEED_38400BPS ; 
 int /*<<< orphan*/  UVSCOM_SPEED_4800BPS ; 
 int /*<<< orphan*/  UVSCOM_SPEED_57600BPS ; 
 int /*<<< orphan*/  UVSCOM_SPEED_600BPS ; 
 int /*<<< orphan*/  UVSCOM_SPEED_9600BPS ; 
 int /*<<< orphan*/  UVSCOM_STOP_BIT_2 ; 
 int /*<<< orphan*/  uvscom_cfg_write (struct uvscom_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
uvscom_cfg_param(struct ucom_softc *ucom, struct termios *t)
{
	struct uvscom_softc *sc = ucom->sc_parent;
	uint16_t value;

	DPRINTF("\n");

	switch (t->c_ospeed) {
	case B150:
		value = UVSCOM_SPEED_150BPS;
		break;
	case B300:
		value = UVSCOM_SPEED_300BPS;
		break;
	case B600:
		value = UVSCOM_SPEED_600BPS;
		break;
	case B1200:
		value = UVSCOM_SPEED_1200BPS;
		break;
	case B2400:
		value = UVSCOM_SPEED_2400BPS;
		break;
	case B4800:
		value = UVSCOM_SPEED_4800BPS;
		break;
	case B9600:
		value = UVSCOM_SPEED_9600BPS;
		break;
	case B19200:
		value = UVSCOM_SPEED_19200BPS;
		break;
	case B38400:
		value = UVSCOM_SPEED_38400BPS;
		break;
	case B57600:
		value = UVSCOM_SPEED_57600BPS;
		break;
	case B115200:
		value = UVSCOM_SPEED_115200BPS;
		break;
	default:
		return;
	}

	uvscom_cfg_write(sc, UVSCOM_SET_SPEED, value);

	value = 0;

	if (t->c_cflag & CSTOPB) {
		value |= UVSCOM_STOP_BIT_2;
	}
	if (t->c_cflag & PARENB) {
		if (t->c_cflag & PARODD) {
			value |= UVSCOM_PARITY_ODD;
		} else {
			value |= UVSCOM_PARITY_EVEN;
		}
	} else {
		value |= UVSCOM_PARITY_NONE;
	}

	switch (t->c_cflag & CSIZE) {
	case CS5:
		value |= UVSCOM_DATA_BIT_5;
		break;
	case CS6:
		value |= UVSCOM_DATA_BIT_6;
		break;
	case CS7:
		value |= UVSCOM_DATA_BIT_7;
		break;
	default:
	case CS8:
		value |= UVSCOM_DATA_BIT_8;
		break;
	}

	uvscom_cfg_write(sc, UVSCOM_SET_PARAM, value);
}