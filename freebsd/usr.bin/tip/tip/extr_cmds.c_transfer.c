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
typedef  scalar_t__ time_t ;
typedef  int /*<<< orphan*/  sig_t ;

/* Variables and functions */
 int BUFSIZ ; 
 int /*<<< orphan*/  FD ; 
 int /*<<< orphan*/  FRAMESIZE ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGIOT ; 
 char STRIP_PAR ; 
 int /*<<< orphan*/  TCSAFLUSH ; 
 int /*<<< orphan*/  VERBOSE ; 
 scalar_t__ any (char,char*) ; 
 scalar_t__ boolean (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccc ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  defchars ; 
 int* fildes ; 
 int /*<<< orphan*/  intbuf ; 
 int /*<<< orphan*/  intcopy ; 
 int /*<<< orphan*/  kill (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int number (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parwrite (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  prtime (char*,scalar_t__) ; 
 int quit ; 
 scalar_t__ read (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/ * repdes ; 
 int /*<<< orphan*/  setjmp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int size (char*) ; 
 int /*<<< orphan*/  tcsetattr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  term ; 
 scalar_t__ time (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipout_pid ; 
 int /*<<< orphan*/  value (int /*<<< orphan*/ ) ; 
 scalar_t__ write (int,char*,int) ; 

__attribute__((used)) static void
transfer(char *buf, int fd, char *eofchars)
{
	int ct, eof;
	char c, buffer[BUFSIZ];
	char *p = buffer;
	size_t cnt;
	time_t start;
	sig_t f;
	char r;

	if (number(value(FRAMESIZE)) > BUFSIZ || number(value(FRAMESIZE)) < 1) {
		printf("framesize must be >= 1 and <= %d\r\n", BUFSIZ);
		close(fd);
		return;
	}

	parwrite(FD, buf, size(buf));
	quit = 0;
	kill(tipout_pid, SIGIOT);
	read(repdes[0], (char *)&ccc, 1);  /* Wait until read process stops */

	/*
	 * finish command
	 */
	r = '\r';
	parwrite(FD, &r, 1);
	do
		read(FD, &c, 1);
	while ((c&STRIP_PAR) != '\n');
	tcsetattr(0, TCSAFLUSH, &defchars);

	(void) setjmp(intbuf);
	f = signal(SIGINT, intcopy);
	start = time(0);
	for (ct = 0; !quit;) {
		eof = read(FD, &c, 1) <= 0;
		c &= STRIP_PAR;
		if (quit)
			continue;
		if (eof || any(c, eofchars))
			break;
		if (c == 0)
			continue;	/* ignore nulls */
		if (c == '\r')
			continue;
		*p++ = c;

		if (c == '\n' && boolean(value(VERBOSE)))
			printf("\r%d", ++ct);
		if ((cnt = (p-buffer)) == (size_t)number(value(FRAMESIZE))) {
			if ((size_t)write(fd, buffer, cnt) != cnt) {
				printf("\r\nwrite error\r\n");
				quit = 1;
			}
			p = buffer;
		}
	}
	if ((cnt = (p-buffer)))
		if ((size_t)write(fd, buffer, cnt) != cnt)
			printf("\r\nwrite error\r\n");

	if (boolean(value(VERBOSE)))
		prtime(" lines transferred in ", time(0)-start);
	tcsetattr(0, TCSAFLUSH, &term);
	write(fildes[1], (char *)&ccc, 1);
	signal(SIGINT, f);
	close(fd);
}