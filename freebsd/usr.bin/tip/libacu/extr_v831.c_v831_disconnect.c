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
 int FD ; 
 int /*<<< orphan*/  TCSAFLUSH ; 
 int /*<<< orphan*/  TIOCCDTR ; 
 int /*<<< orphan*/  TIOCNXCL ; 
 int /*<<< orphan*/  cfsetispeed (struct termios*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfsetospeed (struct termios*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  ioctl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/  tcgetattr (int,struct termios*) ; 
 int /*<<< orphan*/  tcsetattr (int,int /*<<< orphan*/ ,struct termios*) ; 

void
v831_disconnect(void)
{
	struct termios	cntrl;

        sleep(2);
#ifdef DEBUG
        printf("[disconnect: FD=%d]\n", FD);
#endif
        if (FD > 0) {
                ioctl(FD, TIOCCDTR, 0);
		tcgetattr(FD, &cntrl);
		cfsetospeed(&cntrl, 0);
		cfsetispeed(&cntrl, 0);
		tcsetattr(FD, TCSAFLUSH, &cntrl);
                ioctl(FD, TIOCNXCL, NULL);
        }
        close(FD);
}