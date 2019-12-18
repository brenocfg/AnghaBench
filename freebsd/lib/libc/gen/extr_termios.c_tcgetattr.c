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
struct termios {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TIOCGETA ; 
 int _ioctl (int,int /*<<< orphan*/ ,struct termios*) ; 

int
tcgetattr(int fd, struct termios *t)
{

	return (_ioctl(fd, TIOCGETA, t));
}