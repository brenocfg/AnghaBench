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
struct termios {int c_cflag; int c_iflag; int c_lflag; int* c_cc; int /*<<< orphan*/  c_oflag; } ;

/* Variables and functions */
 int CLOCAL ; 
 int CRTSCTS ; 
 int CS8 ; 
 int CSIZE ; 
 int /*<<< orphan*/  DC ; 
 int ECHO ; 
 int /*<<< orphan*/  FD ; 
 int /*<<< orphan*/  HARDWAREFLOW ; 
 int ICANON ; 
 int ICRNL ; 
 int IEXTEN ; 
 int ISIG ; 
 int ISTRIP ; 
 int IXOFF ; 
 int /*<<< orphan*/  OPOST ; 
 int PARENB ; 
 int /*<<< orphan*/  TAND ; 
 int /*<<< orphan*/  TCSAFLUSH ; 
 size_t VMIN ; 
 size_t VTIME ; 
 scalar_t__ boolean (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfsetspeed (struct termios*,int) ; 
 scalar_t__ tcgetattr (int /*<<< orphan*/ ,struct termios*) ; 
 int tcsetattr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct termios*) ; 
 int /*<<< orphan*/  value (int /*<<< orphan*/ ) ; 

int
ttysetup(int speed)
{
	struct termios	cntrl;

	if (tcgetattr(FD, &cntrl))
		return (-1);
	cfsetspeed(&cntrl, speed);
	cntrl.c_cflag &= ~(CSIZE|PARENB);
	cntrl.c_cflag |= CS8;
	if (boolean(value(DC)))
		cntrl.c_cflag |= CLOCAL;
	if (boolean(value(HARDWAREFLOW)))
		cntrl.c_cflag |= CRTSCTS;
	cntrl.c_iflag &= ~(ISTRIP|ICRNL);
	cntrl.c_oflag &= ~OPOST;
	cntrl.c_lflag &= ~(ICANON|ISIG|IEXTEN|ECHO);
	cntrl.c_cc[VMIN] = 1;
	cntrl.c_cc[VTIME] = 0;
	if (boolean(value(TAND)))
		cntrl.c_iflag |= IXOFF;
	return (tcsetattr(FD, TCSAFLUSH, &cntrl));
}