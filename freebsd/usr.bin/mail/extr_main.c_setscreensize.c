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
struct winsize {scalar_t__ ws_col; scalar_t__ ws_row; } ;
struct termios {int dummy; } ;
typedef  scalar_t__ speed_t ;

/* Variables and functions */
 scalar_t__ B1200 ; 
 scalar_t__ B9600 ; 
 int /*<<< orphan*/  TIOCGWINSZ ; 
 scalar_t__ cfgetospeed (struct termios*) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,char*) ; 
 int realscreenheight ; 
 int screenheight ; 
 scalar_t__ screenwidth ; 
 scalar_t__ tcgetattr (int,struct termios*) ; 

void
setscreensize(void)
{
	struct termios tbuf;
	struct winsize ws;
	speed_t speed;

	if (ioctl(1, TIOCGWINSZ, (char *)&ws) < 0)
		ws.ws_col = ws.ws_row = 0;
	if (tcgetattr(1, &tbuf) < 0)
		speed = B9600;
	else
		speed = cfgetospeed(&tbuf);
	if (speed < B1200)
		screenheight = 9;
	else if (speed == B1200)
		screenheight = 14;
	else if (ws.ws_row != 0)
		screenheight = ws.ws_row;
	else
		screenheight = 24;
	if ((realscreenheight = ws.ws_row) == 0)
		realscreenheight = 24;
	if ((screenwidth = ws.ws_col) == 0)
		screenwidth = 80;
}