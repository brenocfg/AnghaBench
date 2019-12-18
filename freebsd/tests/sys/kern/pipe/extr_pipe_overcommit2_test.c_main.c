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
 scalar_t__ EMFILE ; 
 scalar_t__ ENFILE ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int mkstemp (char*) ; 
 unsigned int nitems (int*) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int pipe (int*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  unlink (char*) ; 

int
main(void)
{
	char template[] = "pipe.XXXXXXXXXX";
	int lastfd, pipes[10000], returnval;
	unsigned int i;

	lastfd = -1;

	if (mkstemp(template) == -1)
		err(1, "mkstemp failed");

	for (i = 0; i < nitems(pipes); i++) {
		returnval = open(template, O_RDONLY);
		if (returnval == -1 && (errno == ENFILE || errno == EMFILE))
			break; /* All descriptors exhausted. */
		else
			lastfd = returnval;
	}

	/* First falloc failure case in sys_pipe.c:pipe() */
	for (i = 0; i < 1000; i++) {
		returnval = pipe(&pipes[i]);
	}

	/*
	 * Free just one FD so that the second falloc failure
	 * case will occur.
	 */
	close(lastfd);

	for (i = 0; i < 1000; i++) {
		returnval = pipe(&pipes[i]);
	}
	printf("PASS\n");

	unlink(template);

	exit(0);
}