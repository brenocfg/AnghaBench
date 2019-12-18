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

/* Variables and functions */
 int /*<<< orphan*/  DUMBUFLEN ; 
 int /*<<< orphan*/  FD ; 
 int /*<<< orphan*/  FIONREAD ; 
 int /*<<< orphan*/  TCIOFLUSH ; 
 int /*<<< orphan*/  TIOCCDTR ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 char* dumbuf ; 
 char gobble (char*) ; 
 scalar_t__ hay_sync () ; 
 int /*<<< orphan*/  ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  min (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 size_t read (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 size_t rlen ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/  tcflush (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void
goodbye(void)
{
	int len;
	char c;

	tcflush(FD, TCIOFLUSH);
	if (hay_sync()) {
		sleep(1);
#ifndef DEBUG
		tcflush(FD, TCIOFLUSH);
#endif
		write(FD, "ATH0\r", 5);		/* insurance */
#ifndef DEBUG
		c = gobble("03");
		if (c != '0' && c != '3') {
			printf("cannot hang up modem\n\r");
			printf("please use 'tip dialer' to make sure the line is hung up\n\r");
		}
#endif
		sleep(1);
		ioctl(FD, FIONREAD, &len);
#ifdef DEBUG
		printf("goodbye1: len=%d -- ", len);
		rlen = read(FD, dumbuf, min(len, DUMBUFLEN));
		dumbuf[rlen] = '\0';
		printf("read (%d): %s\r\n", rlen, dumbuf);
#endif
		write(FD, "ATv1\r", 5);
		sleep(1);
#ifdef DEBUG
		ioctl(FD, FIONREAD, &len);
		printf("goodbye2: len=%d -- ", len);
		rlen = read(FD, dumbuf, min(len, DUMBUFLEN));
		dumbuf[rlen] = '\0';
		printf("read (%d): %s\r\n", rlen, dumbuf);
#endif
	}
	tcflush(FD, TCIOFLUSH);
	ioctl(FD, TIOCCDTR, 0);		/* clear DTR (insurance) */
	close(FD);
}