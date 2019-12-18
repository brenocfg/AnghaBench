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
struct winsize {int dummy; } ;
struct termios {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  close (int) ; 
 int fork () ; 
 int /*<<< orphan*/  login_tty (int) ; 
 int openpty (int*,int*,char*,struct termios*,struct winsize*) ; 

int
forkpty(int *amaster, char *name, struct termios *termp, struct winsize *winp)
{
	int master, slave, pid;

	if (openpty(&master, &slave, name, termp, winp) == -1)
		return (-1);
	switch (pid = fork()) {
	case -1:
		(void)close(slave);
		return (-1);
	case 0:
		/*
		 * child
		 */
		(void)close(master);
		login_tty(slave);
		return (0);
	}
	/*
	 * parent
	 */
	*amaster = master;
	(void) close(slave);
	return (pid);
}