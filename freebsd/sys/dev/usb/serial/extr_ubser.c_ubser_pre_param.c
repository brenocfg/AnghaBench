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
struct ucom_softc {int dummy; } ;
struct termios {int c_ospeed; int c_cflag; } ;

/* Variables and functions */
 int CCAR_OFLOW ; 
 int CDSR_OFLOW ; 
 int CDTR_IFLOW ; 
 int CRTS_IFLOW ; 
#define  CS8 128 
 int CSIZE ; 
 int CSTOPB ; 
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int EINVAL ; 
 int PARENB ; 

__attribute__((used)) static int
ubser_pre_param(struct ucom_softc *ucom, struct termios *t)
{
	DPRINTF("\n");

	/*
	 * The firmware on our devices can only do 8n1@9600bps
	 * without handshake.
	 * We refuse to accept other configurations.
	 */

	/* ensure 9600bps */
	switch (t->c_ospeed) {
	case 9600:
		break;
	default:
		return (EINVAL);
	}

	/* 2 stop bits not possible */
	if (t->c_cflag & CSTOPB)
		return (EINVAL);

	/* XXX parity handling not possible with current firmware */
	if (t->c_cflag & PARENB)
		return (EINVAL);

	/* we can only do 8 data bits */
	switch (t->c_cflag & CSIZE) {
	case CS8:
		break;
	default:
		return (EINVAL);
	}

	/* we can't do any kind of hardware handshaking */
	if ((t->c_cflag &
	    (CRTS_IFLOW | CDTR_IFLOW | CDSR_OFLOW | CCAR_OFLOW)) != 0)
		return (EINVAL);

	/*
	 * XXX xon/xoff not supported by the firmware!
	 * This is handled within FreeBSD only and may overflow buffers
	 * because of delayed reaction due to device buffering.
	 */

	return (0);
}