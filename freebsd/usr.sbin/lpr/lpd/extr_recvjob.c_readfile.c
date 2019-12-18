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
struct printer {int /*<<< orphan*/  printer; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  FILMOD ; 
 int O_CREAT ; 
 int O_EXCL ; 
 int O_WRONLY ; 
 int SPL_BUFSIZ ; 
 int /*<<< orphan*/  STDOUT_FILENO ; 
 int /*<<< orphan*/  ack () ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  frecverr (char*,int /*<<< orphan*/ ,...) ; 
 scalar_t__ noresponse () ; 
 int open (char*,int,int /*<<< orphan*/ ) ; 
 int read (int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/ * strchr (char*,char) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlink (char*) ; 
 scalar_t__ write (int,char*,size_t) ; 

__attribute__((used)) static int
readfile(struct printer *pp, char *file, size_t size)
{
	register char *cp;
	char buf[SPL_BUFSIZ];
	size_t amt, i;
	int err, fd, j;

	fd = open(file, O_CREAT|O_EXCL|O_WRONLY, FILMOD);
	if (fd < 0) {
		frecverr("%s: readfile: error on open(%s): %s",
			 pp->printer, file, strerror(errno));
		/*NOTREACHED*/
	}
	ack();
	err = 0;
	for (i = 0; i < size; i += SPL_BUFSIZ) {
		amt = SPL_BUFSIZ;
		cp = buf;
		if (i + amt > size)
			amt = size - i;
		do {
			j = read(STDOUT_FILENO, cp, amt);
			if (j <= 0) {
				frecverr("%s: lost connection", pp->printer);
				/*NOTREACHED*/
			}
			amt -= j;
			cp += j;
		} while (amt > 0);
		amt = SPL_BUFSIZ;
		if (i + amt > size)
			amt = size - i;
		if (write(fd, buf, amt) != (ssize_t)amt) {
			err++;
			break;
		}
	}
	(void) close(fd);
	if (err) {
		frecverr("%s: write error on close(%s)", pp->printer, file);
		/*NOTREACHED*/
	}
	if (noresponse()) {		/* file sent had bad data in it */
		if (strchr(file, '/') == NULL)
			(void) unlink(file);
		return (0);
	}
	ack();
	return (1);
}