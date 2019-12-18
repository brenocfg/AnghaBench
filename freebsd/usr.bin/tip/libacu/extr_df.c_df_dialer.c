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
struct termios {int /*<<< orphan*/  c_cflag; } ;

/* Variables and functions */
 int B1200 ; 
 int FD ; 
 int /*<<< orphan*/  HUPCL ; 
 int /*<<< orphan*/  SIGALRM ; 
 int /*<<< orphan*/  Sjbuf ; 
 int /*<<< orphan*/  TCIOFLUSH ; 
 int /*<<< orphan*/  TCSAFLUSH ; 
 int /*<<< orphan*/  TCSANOW ; 
 int /*<<< orphan*/  TIOCMBIC ; 
 int /*<<< orphan*/  TIOCMBIS ; 
 int TIOCM_ST ; 
 int /*<<< orphan*/  VERBOSE ; 
 int /*<<< orphan*/  alarm (int) ; 
 int /*<<< orphan*/  alrm_timeout ; 
 scalar_t__ boolean (int /*<<< orphan*/ ) ; 
 int cfgetospeed (struct termios*) ; 
 int /*<<< orphan*/  cfsetispeed (struct termios*,int) ; 
 int /*<<< orphan*/  cfsetospeed (struct termios*,int) ; 
 int /*<<< orphan*/  df_disconnect () ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ioctl (int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  read (int,char*,int) ; 
 scalar_t__ setjmp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/  stdout ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  tcflush (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcgetattr (int,struct termios*) ; 
 int /*<<< orphan*/  tcsetattr (int,int /*<<< orphan*/ ,struct termios*) ; 
 int /*<<< orphan*/  value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write (int,char*,int) ; 

__attribute__((used)) static int
df_dialer(char *num, char *acu, int df03)
{
	int f = FD;
	struct termios cntrl;
	int speed = 0;
	char c = '\0';

	tcgetattr(f, &cntrl);
	cntrl.c_cflag |= HUPCL;
	tcsetattr(f, TCSANOW, &cntrl);
	if (setjmp(Sjbuf)) {
		printf("connection timed out\r\n");
		df_disconnect();
		return (0);
	}
	if (boolean(value(VERBOSE)))
		printf("\ndialing...");
	fflush(stdout);
#ifdef TIOCMSET
	if (df03) {
		int st = TIOCM_ST;	/* secondary Transmit flag */

		tcgetattr(f, &cntrl);
		speed = cfgetospeed(&cntrl);
		if (speed != B1200) {	/* must dial at 1200 baud */
			cfsetospeed(&cntrl, B1200);
			cfsetispeed(&cntrl, B1200);
			tcsetattr(f, TCSAFLUSH, &cntrl);
			ioctl(f, TIOCMBIC, &st); /* clear ST for 300 baud */
		} else
			ioctl(f, TIOCMBIS, &st); /* set ST for 1200 baud */
	}
#endif
	signal(SIGALRM, alrm_timeout);
	alarm(5 * strlen(num) + 10);
	tcflush(f, TCIOFLUSH);
	write(f, "\001", 1);
	sleep(1);
	write(f, "\002", 1);
	write(f, num, strlen(num));
	read(f, &c, 1);
#ifdef TIOCMSET
	if (df03 && speed != B1200) {
		cfsetospeed(&cntrl, speed);
		cfsetispeed(&cntrl, speed);
		tcsetattr(f, TCSAFLUSH, &cntrl);
	}
#endif
	return (c == 'A');
}