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
 int EX_NOINPUT ; 
 int EX_OK ; 
 int EX_OSERR ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int fsync (int) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  warn (char*,char*) ; 

int
main(int argc, char *argv[])
{
	int fd;
	int i;
	int rval;
	
	if (argc < 2) {
		usage();
		/* NOTREACHED */
	}
	
	rval = EX_OK;
	for (i = 1; i < argc; ++i) {
		if ((fd = open(argv[i], O_RDONLY)) == -1) {
			warn("open %s", argv[i]);
			if (rval == EX_OK)
				rval = EX_NOINPUT;
			continue;
		}

		if (fsync(fd) == -1) {
			warn("fsync %s", argv[i]);
			if (rval == EX_OK)
				rval = EX_OSERR;
		}
		close(fd);
	}
	exit(rval);
	/* NOTREACHED */
}