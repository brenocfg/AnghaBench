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
 int LINELENGTH ; 
 int /*<<< orphan*/  ROTATE (int,int) ; 
 int /*<<< orphan*/  STDIN_FILENO ; 
 int /*<<< orphan*/  bzero (int*,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ isascii (int) ; 
 scalar_t__ islower (int) ; 
 scalar_t__ isupper (int) ; 
 int log (double) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  printit (char*) ; 
 int /*<<< orphan*/  putchar (int /*<<< orphan*/ ) ; 
 int read (int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  stderr ; 
 int* stdf ; 
 char* strerror (int /*<<< orphan*/ ) ; 

int
main(int argc, char **argv)
{
	int ch, dot, i, nread, winnerdot = 0;
	char *inbuf;
	int obs[26], try, winner;

	if (argc > 1)
		printit(argv[1]);

	if (!(inbuf = malloc((size_t)LINELENGTH))) {
		(void)fprintf(stderr, "caesar: out of memory.\n");
		exit(1);
	}

	/* adjust frequency table to weight low probs REAL low */
	for (i = 0; i < 26; ++i)
		stdf[i] = log(stdf[i]) + log(26.0 / 100.0);

	/* zero out observation table */
	bzero(obs, 26 * sizeof(int));

	if ((nread = read(STDIN_FILENO, inbuf, (size_t)LINELENGTH)) < 0) {
		(void)fprintf(stderr, "caesar: %s\n", strerror(errno));
		exit(1);
	}
	for (i = nread; i--;) {
		ch = (unsigned char) inbuf[i];
		if (isascii(ch)) {
			if (islower(ch))
				++obs[ch - 'a'];
			else if (isupper(ch))
				++obs[ch - 'A'];
		}
	}

	/*
	 * now "dot" the freqs with the observed letter freqs
	 * and keep track of best fit
	 */
	for (try = winner = 0; try < 26; ++try) { /* += 13) { */
		dot = 0;
		for (i = 0; i < 26; i++)
			dot += obs[i] * stdf[(i + try) % 26];
		/* initialize winning score */
		if (try == 0)
			winnerdot = dot;
		if (dot > winnerdot) {
			/* got a new winner! */
			winner = try;
			winnerdot = dot;
		}
	}

	for (;;) {
		for (i = 0; i < nread; ++i) {
			ch = (unsigned char) inbuf[i];
			putchar(ROTATE(ch, winner));
		}
		if (nread < LINELENGTH)
			break;
		if ((nread = read(STDIN_FILENO, inbuf, (size_t)LINELENGTH)) < 0) {
			(void)fprintf(stderr, "caesar: %s\n", strerror(errno));
			exit(1);
		}
	}
	exit(0);
}