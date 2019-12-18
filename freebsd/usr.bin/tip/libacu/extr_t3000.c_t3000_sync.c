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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  FD ; 
 int /*<<< orphan*/  FIONREAD ; 
 int /*<<< orphan*/  MAXRETRY ; 
 int /*<<< orphan*/  TCIOFLUSH ; 
 int /*<<< orphan*/  TIOCCDTR ; 
 int /*<<< orphan*/  TIOCSDTR ; 
 int /*<<< orphan*/  bzero (char*,int) ; 
 int /*<<< orphan*/  ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int read (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  sleep (int) ; 
 scalar_t__ strchr (char*,char) ; 
 int /*<<< orphan*/  t3000_write (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  tcflush (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
t3000_sync(void)
{
	int already = 0;
	int len;
	char buf[40];

	while (already++ < MAXRETRY) {
		tcflush(FD, TCIOFLUSH);
		t3000_write(FD, "\rAT Z\r", 6);	/* reset modem */
		bzero(buf, sizeof(buf));
		sleep(2);
		ioctl(FD, FIONREAD, &len);
#if 1
if (len == 0) len = 1;
#endif
		if (len) {
			len = read(FD, buf, sizeof(buf));
#ifdef DEBUG
			buf[len] = '\0';
			printf("t3000_sync: (\"%s\")\n\r", buf);
#endif
			if (strchr(buf, '0') || 
		   	   (strchr(buf, 'O') && strchr(buf, 'K')))
				return(1);
		}
		/*
		 * If not strapped for DTR control,
		 * try to get command mode.
		 */
		sleep(1);
		t3000_write(FD, "+++", 3);
		sleep(1);
		/*
		 * Toggle DTR to force anyone off that might have left
		 * the modem connected.
		 */
		ioctl(FD, TIOCCDTR, 0);
		sleep(1);
		ioctl(FD, TIOCSDTR, 0);
	}
	t3000_write(FD, "\rAT Z\r", 6);
	return (0);
}