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
 int BUFSIZ ; 
 scalar_t__ EOF ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 scalar_t__ putchar (char) ; 
 int /*<<< orphan*/  setbuf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stdout ; 

int
main(int argc, char **argv)
{
	int len, count;
	register int i, j, fc, nc;
	char outbuf[BUFSIZ];

	setbuf(stdout, outbuf);
	if (argc >= 2)
		len = atoi(argv[1]);
	else
		len = 79;
	if (argc >= 3)
		count = atoi(argv[2]);
	else
		count = 200;
	fc = ' ';
	for (i = 0; i < count; i++) {
		if (++fc == 0177)
			fc = ' ';
		nc = fc;
		for (j = 0; j < len; j++) {
			if (putchar(nc) == EOF)
				err(1, "Write error");
			if (++nc == 0177)
				nc = ' ';
		}
		if (putchar('\n') == EOF)
			err(1, "Write error");
	}
	(void) fflush(stdout);
	exit(0);
}