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
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int FD ; 
 int /*<<< orphan*/  FIONREAD ; 
 int MAXRETRY ; 
 int /*<<< orphan*/  TIOCCDTR ; 
 int /*<<< orphan*/  TIOCSDTR ; 
 int /*<<< orphan*/  delay (int,int) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ min (int,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  read (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/  write (int,char*,int) ; 

__attribute__((used)) static int
vensync(int fd)
{
	int already = 0, nread;
	char buf[60];

	/*
	 * Toggle DTR to force anyone off that might have left
	 * the modem connected, and insure a consistent state
	 * to start from.
	 *
	 * If you don't have the ioctl calls to diddle directly
	 * with DTR, you can always try setting the baud rate to 0.
	 */
	ioctl(FD, TIOCCDTR, 0);
	sleep(1);
	ioctl(FD, TIOCSDTR, 0);
	while (already < MAXRETRY) {
		/*
		 * After reseting the modem, send it two \r's to
		 * autobaud on. Make sure to delay between them
		 * so the modem can frame the incoming characters.
		 */
		write(fd, "\r", 1);
		delay(1,10);
		write(fd, "\r", 1);
		sleep(2);
		if (ioctl(fd, FIONREAD, (caddr_t)&nread) < 0) {
			perror("tip: ioctl");
			continue;
		}
		while (nread > 0) {
			read(fd, buf, min(nread, 60));
			if ((buf[nread - 1] & 0177) == '$')
				return (1);
			nread -= min(nread, 60);
		}
		sleep(1);
		already++;
	}
	return (0);
}