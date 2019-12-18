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
typedef  scalar_t__ ssize_t ;
typedef  scalar_t__ off_t ;

/* Variables and functions */
 int /*<<< orphan*/  MKFILE_FLAG ; 
 int /*<<< orphan*/  MKFILE_MODE ; 
 unsigned long long MKFILE_WBUF ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  buf ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,unsigned long long) ; 
 scalar_t__ lseek (int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nofill ; 
 int open (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ verbose ; 
 scalar_t__ write (int,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static int
create_file(char *f, unsigned long long s)
{
	int fd;
	size_t w;
	ssize_t ws;

	if (verbose) {
		fprintf(stdout, "%s %llu bytes\n", f, s);
		fflush(stdout);
	}

	/* Open file to create. */
	if ((fd = open(f, MKFILE_FLAG, MKFILE_MODE)) < 0) {
		return -1;
	}

	/* Seek to the end and write 1 byte. */
	if ((lseek(fd, (off_t)(s - 1LL), SEEK_SET) == (off_t)-1) ||
	    (write(fd, buf, (size_t)1) == (ssize_t)-1)) {
		/*
		 * We don't close(fd) here to avoid overwriting errno.
		 * This is fd-leak, but is not harmful
		 * because returning error causes mkfile(8) to exit.
		 */
		return -1;
	}

	/* Fill. */
	if (!nofill) {
		if (lseek(fd, (off_t)0, SEEK_SET) == (off_t)-1) {
			/* Same as above. */
			return -1;
		}
		while (s) {
			w = (s > MKFILE_WBUF) ? MKFILE_WBUF : s;
			if ((ws = write(fd, buf, w)) == (ssize_t)-1) {
				/* Same as above. */
				return -1;
			}
			s -= ws;
		}
	}
	close(fd);

	return 0;
}