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
typedef  int uid_t ;
typedef  scalar_t__ u_int ;
typedef  int mode_t ;
typedef  int gid_t ;
typedef  scalar_t__ dev_t ;

/* Variables and functions */
 int S_IFBLK ; 
 int S_IFCHR ; 
 int a_gid (char*) ; 
 int a_uid (char*) ; 
 scalar_t__ chown (char*,int,int) ; 
 int /*<<< orphan*/  err (int,char*,char*) ; 
 int errno ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 long major (scalar_t__) ; 
 scalar_t__ makedev (long,long) ; 
 scalar_t__ minor (scalar_t__) ; 
 scalar_t__ mknod (char*,int,scalar_t__) ; 
 char* strchr (char*,char) ; 
 scalar_t__ strtoul (char*,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, char **argv)
{
	int range_error;
	uid_t uid;
	gid_t gid;
	mode_t mode;
	dev_t dev;
	char *cp, *endp;
	long mymajor, myminor;

	if (argc != 2 && argc != 5 && argc != 6)
		usage();

	if (argc >= 5) {
		mode = 0666;
		if (argv[2][0] == 'c')
			mode |= S_IFCHR;
		else if (argv[2][0] == 'b')
			mode |= S_IFBLK;
		else
			errx(1, "node must be type 'b' or 'c'");

		errno = 0;
		mymajor = (long)strtoul(argv[3], &endp, 0);
		if (endp == argv[3] || *endp != '\0')
			errx(1, "%s: non-numeric major number", argv[3]);
		range_error = errno;
		errno = 0;
		myminor = (long)strtoul(argv[4], &endp, 0);
		if (endp == argv[4] || *endp != '\0')
			errx(1, "%s: non-numeric minor number", argv[4]);
		range_error |= errno;
		dev = makedev(mymajor, myminor);
		if (range_error || major(dev) != mymajor ||
		    (long)(u_int)minor(dev) != myminor)
			errx(1, "major or minor number too large");
	} else {
		mode = 0666 | S_IFCHR;
		dev = 0;
	}

	uid = gid = -1;
	if (6 == argc) {
	    	/* have owner:group */
		if ((cp = strchr(argv[5], ':')) != NULL) {
			*cp++ = '\0';
			gid = a_gid(cp);
		} else
		usage();
		uid = a_uid(argv[5]);
	}

	if (mknod(argv[1], mode, dev) != 0)
		err(1, "%s", argv[1]);
	if (6 == argc)
		if (chown(argv[1], uid, gid))
			err(1, "setting ownership on %s", argv[1]);
	exit(0);
}