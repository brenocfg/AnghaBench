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
 int O_NOCTTY ; 
 int O_RDWR ; 
 int /*<<< orphan*/  TCSAFLUSH ; 
 int /*<<< orphan*/  TIOCSWINSZ ; 
 int /*<<< orphan*/  close (int) ; 
 int grantpt (int) ; 
 int /*<<< orphan*/  ioctl (int,int /*<<< orphan*/ ,char*) ; 
 int open (char const*,int) ; 
 int posix_openpt (int) ; 
 char* ptsname (int) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int /*<<< orphan*/  tcsetattr (int,int /*<<< orphan*/ ,struct termios*) ; 
 int unlockpt (int) ; 

int
openpty(int *amaster, int *aslave, char *name, struct termios *termp,
    struct winsize *winp)
{
	const char *slavename;
	int master, slave;

	master = posix_openpt(O_RDWR|O_NOCTTY);
	if (master == -1)
		return (-1);

	if (grantpt(master) == -1)
		goto bad;

	if (unlockpt(master) == -1)
		goto bad;

	slavename = ptsname(master);
	if (slavename == NULL)
		goto bad;

	slave = open(slavename, O_RDWR);
	if (slave == -1)
		goto bad;

	*amaster = master;
	*aslave = slave;

	if (name)
		strcpy(name, slavename);
	if (termp)
		tcsetattr(slave, TCSAFLUSH, termp);
	if (winp)
		ioctl(slave, TIOCSWINSZ, (char *)winp);

	return (0);

bad:	close(master);
	return (-1);
}