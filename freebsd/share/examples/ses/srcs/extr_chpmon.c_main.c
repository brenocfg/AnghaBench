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
typedef  int ses_encstat ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int BADSTAT ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  SESIOC_GETENCSTAT ; 
 int /*<<< orphan*/  SESIOC_SETENCSTAT ; 
 int SES_ENCSTAT_CRITICAL ; 
 int SES_ENCSTAT_NONCRITICAL ; 
 int SES_ENCSTAT_UNRECOV ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  bzero (void*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int* malloc (int) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  putchar (char) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 char* strerror (int /*<<< orphan*/ ) ; 

int
main(int a, char **v)
{
	int fd, delay, dev;
	ses_encstat stat, *carray;

	if (a < 3) {
		fprintf(stderr, "usage: %s polling-interval device "
		    "[ device ... ]\n", *v);
		return (1);
	}
	delay = atoi(v[1]);
	carray = malloc(a);
	if (carray == NULL) {
		perror("malloc");
		return (1);
	}
	bzero((void *)carray, a);

	for (;;) {
		for (dev = 2; dev < a; dev++) {
			fd = open(v[dev], O_RDWR);
			if (fd < 0) {
				perror(v[dev]);
				continue;
			}
			/*
			 * First clear any enclosure status, in case it is
			 * a latched status.
			 */
			stat = 0;
			if (ioctl(fd, SESIOC_SETENCSTAT, (caddr_t) &stat) < 0) {
				fprintf(stderr, "%s: SESIOC_SETENCSTAT1: %s\n",
				    v[dev], strerror(errno));
				(void) close(fd);
				continue;
			}
			/*
			 * Now get the actual current enclosure status.
			 */
			if (ioctl(fd, SESIOC_GETENCSTAT, (caddr_t) &stat) < 0) {
				fprintf(stderr, "%s: SESIOC_GETENCSTAT: %s\n",
				    v[dev], strerror(errno));
				(void) close(fd);
				continue;
			}

			if ((stat & BADSTAT) == 0) {
				if (carray[dev]) {
					fprintf(stdout, "%s: Clearing CRITICAL "
					    "condition\n", v[dev]);
					carray[dev] = 0;
				}
				(void) close(fd);
				continue;
			}
			carray[dev] = 1;
			fprintf(stdout, "%s: Setting CRITICAL from:", v[dev]);
			if (stat & SES_ENCSTAT_UNRECOV)
				fprintf(stdout, " UNRECOVERABLE");
		
			if (stat & SES_ENCSTAT_CRITICAL)
				fprintf(stdout, " CRITICAL");
		
			if (stat & SES_ENCSTAT_NONCRITICAL)
				fprintf(stdout, " NONCRITICAL");
			putchar('\n');
			stat = SES_ENCSTAT_CRITICAL;
			if (ioctl(fd, SESIOC_SETENCSTAT, (caddr_t) &stat) < 0) {
				fprintf(stderr, "%s: SESIOC_SETENCSTAT 2: %s\n",
				    v[dev], strerror(errno));
			}
			(void) close(fd);
		}
		sleep(delay);
	}
	/* NOTREACHED */
}