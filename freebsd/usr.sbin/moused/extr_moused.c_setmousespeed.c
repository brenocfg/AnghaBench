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
typedef  scalar_t__ tcflag_t ;
struct termios {int c_iflag; int* c_cc; scalar_t__ c_cflag; scalar_t__ c_lflag; scalar_t__ c_oflag; } ;
struct TYPE_2__ {scalar_t__ rtype; int /*<<< orphan*/  mfd; } ;

/* Variables and functions */
 int /*<<< orphan*/  B1200 ; 
 int /*<<< orphan*/  B2400 ; 
 int /*<<< orphan*/  B4800 ; 
 int /*<<< orphan*/  B9600 ; 
 int IGNBRK ; 
 int IGNPAR ; 
 scalar_t__ MOUSE_PROTO_LOGI ; 
 scalar_t__ MOUSE_PROTO_LOGIMOUSEMAN ; 
 int /*<<< orphan*/  TCSADRAIN ; 
 size_t VMIN ; 
 size_t VTIME ; 
 int /*<<< orphan*/  cfsetispeed (struct termios*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfsetospeed (struct termios*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  logwarn (char*) ; 
 TYPE_1__ rodent ; 
 scalar_t__ tcgetattr (int /*<<< orphan*/ ,struct termios*) ; 
 scalar_t__ tcsetattr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct termios*) ; 
 int /*<<< orphan*/  usleep (int) ; 
 int write (int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static void
setmousespeed(int old, int new, unsigned cflag)
{
	struct termios tty;
	const char *c;

	if (tcgetattr(rodent.mfd, &tty) < 0)
	{
		logwarn("unable to get status of mouse fd");
		return;
	}

	tty.c_iflag = IGNBRK | IGNPAR;
	tty.c_oflag = 0;
	tty.c_lflag = 0;
	tty.c_cflag = (tcflag_t)cflag;
	tty.c_cc[VTIME] = 0;
	tty.c_cc[VMIN] = 1;

	switch (old)
	{
	case 9600:
		cfsetispeed(&tty, B9600);
		cfsetospeed(&tty, B9600);
		break;
	case 4800:
		cfsetispeed(&tty, B4800);
		cfsetospeed(&tty, B4800);
		break;
	case 2400:
		cfsetispeed(&tty, B2400);
		cfsetospeed(&tty, B2400);
		break;
	case 1200:
	default:
		cfsetispeed(&tty, B1200);
		cfsetospeed(&tty, B1200);
	}

	if (tcsetattr(rodent.mfd, TCSADRAIN, &tty) < 0)
	{
		logwarn("unable to set status of mouse fd");
		return;
	}

	switch (new)
	{
	case 9600:
		c = "*q";
		cfsetispeed(&tty, B9600);
		cfsetospeed(&tty, B9600);
		break;
	case 4800:
		c = "*p";
		cfsetispeed(&tty, B4800);
		cfsetospeed(&tty, B4800);
		break;
	case 2400:
		c = "*o";
		cfsetispeed(&tty, B2400);
		cfsetospeed(&tty, B2400);
		break;
	case 1200:
	default:
		c = "*n";
		cfsetispeed(&tty, B1200);
		cfsetospeed(&tty, B1200);
	}

	if (rodent.rtype == MOUSE_PROTO_LOGIMOUSEMAN
	    || rodent.rtype == MOUSE_PROTO_LOGI)
	{
		if (write(rodent.mfd, c, 2) != 2)
		{
			logwarn("unable to write to mouse fd");
			return;
		}
	}
	usleep(100000);

	if (tcsetattr(rodent.mfd, TCSADRAIN, &tty) < 0)
		logwarn("unable to set status of mouse fd");
}