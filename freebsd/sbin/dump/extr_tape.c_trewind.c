#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct stat {int /*<<< orphan*/  st_mode; } ;
struct TYPE_2__ {int fd; scalar_t__ sent; } ;

/* Variables and functions */
 int SLAVES ; 
 scalar_t__ S_ISFIFO (int /*<<< orphan*/ ) ; 
 int atomic (int /*<<< orphan*/ ,int,char*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  dumpabort (int /*<<< orphan*/ ) ; 
 scalar_t__ fstat (int,struct stat*) ; 
 scalar_t__ host ; 
 int /*<<< orphan*/  msg (char*,...) ; 
 int open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perror (char*) ; 
 scalar_t__ pipeout ; 
 int /*<<< orphan*/ * popenfp ; 
 scalar_t__ popenout ; 
 int /*<<< orphan*/  quit (char*) ; 
 int /*<<< orphan*/  read ; 
 int /*<<< orphan*/  rmtclose () ; 
 scalar_t__ rmtopen (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* slaves ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/  tape ; 
 int tapefd ; 
 scalar_t__ wait (int*) ; 
 int writesize ; 

void
trewind(void)
{
	struct stat sb;
	int f;
	int got;

	for (f = 0; f < SLAVES; f++) {
		/*
		 * Drain the results, but unlike EOT we DO (or should) care
		 * what the return values were, since if we detect EOT after
		 * we think we've written the last blocks to the tape anyway,
		 * we have to replay those blocks with rollforward.
		 *
		 * fixme: punt for now.
		 */
		if (slaves[f].sent) {
			if (atomic(read, slaves[f].fd, (char *)&got, sizeof got)
			    != sizeof got) {
				perror("  DUMP: error reading command pipe in master");
				dumpabort(0);
			}
			slaves[f].sent = 0;
			if (got != writesize) {
				msg("EOT detected in last 2 tape records!\n");
				msg("Use a longer tape, decrease the size estimate\n");
				quit("or use no size estimate at all.\n");
			}
		}
		(void) close(slaves[f].fd);
	}
	while (wait((int *)NULL) >= 0)	/* wait for any signals from slaves */
		/* void */;

	if (pipeout)
		return;

	msg("Closing %s\n", tape);

	if (popenout) {
		tapefd = -1;
		(void)pclose(popenfp);
		popenfp = NULL;
		return;
	}
#ifdef RDUMP
	if (host) {
		rmtclose();
		while (rmtopen(tape, 0) < 0)
			sleep(10);
		rmtclose();
		return;
	}
#endif
	if (fstat(tapefd, &sb) == 0 && S_ISFIFO(sb.st_mode)) {
		(void)close(tapefd);
		return;
	}
	(void) close(tapefd);
	while ((f = open(tape, 0)) < 0)
		sleep (10);
	(void) close(f);
}