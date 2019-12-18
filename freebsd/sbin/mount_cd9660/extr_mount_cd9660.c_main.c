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
struct iovec {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EX_OSERR ; 
 int MAXPATHLEN ; 
 int MNT_RDONLY ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  build_iovec (struct iovec**,int*,char*,char*,size_t) ; 
 int /*<<< orphan*/  build_iovec_argf (struct iovec**,int*,char*,char*,int) ; 
 scalar_t__ checkpath (char*,char*) ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int get_ssector (char*) ; 
 int /*<<< orphan*/  getmntopts (char*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  mopts ; 
 scalar_t__ nmount (struct iovec*,int,int) ; 
 char* optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  rmslashes (char*,char*) ; 
 int set_charset (struct iovec**,int*,char*) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, char **argv)
{
	struct iovec *iov;
	int iovlen;
	int ch, mntflags;
	char *dev, *dir, *p, *val, mntpath[MAXPATHLEN];
	int verbose;
	int ssector;		/* starting sector, 0 for 1st session */
	char fstype[] = "cd9660";

	iov = NULL;
	iovlen = 0;
	mntflags = verbose = 0;
	ssector = -1;

	while ((ch = getopt(argc, argv, "begjo:rs:vC:")) != -1)
		switch (ch) {
		case 'b':
			build_iovec(&iov, &iovlen, "brokenjoliet", NULL, (size_t)-1);
			break;
		case 'e':
			build_iovec(&iov, &iovlen, "extatt", NULL, (size_t)-1);
			break;
		case 'g':
			build_iovec(&iov, &iovlen, "gens", NULL, (size_t)-1);
			break;
		case 'j':
			build_iovec(&iov, &iovlen, "nojoliet", NULL, (size_t)-1);
			break;
		case 'o':
			getmntopts(optarg, mopts, &mntflags, NULL);
			p = strchr(optarg, '=');
			val = NULL;
			if (p != NULL) {
				*p = '\0';
				val = p + 1;
			}
			build_iovec(&iov, &iovlen, optarg, val, (size_t)-1);
			break;
		case 'r':
			build_iovec(&iov, &iovlen, "norrip", NULL, (size_t)-1);
			break;
		case 's':
			ssector = atoi(optarg);
			break;
		case 'v':
			verbose++;
			break;
		case 'C':
			if (set_charset(&iov, &iovlen, optarg) == -1)
				err(EX_OSERR, "cd9660_iconv");
			build_iovec(&iov, &iovlen, "kiconv", NULL, (size_t)-1);
			break;
		case '?':
		default:
			usage();
		}
	argc -= optind;
	argv += optind;

	if (argc != 2)
		usage();

	dev = argv[0];
	dir = argv[1];

	/*
	 * Resolve the mountpoint with realpath(3) and remove unnecessary
	 * slashes from the devicename if there are any.
	 */
	if (checkpath(dir, mntpath) != 0)
		err(1, "%s", mntpath);
	(void)rmslashes(dev, dev);

	if (ssector == -1) {
		/*
		 * The start of the session has not been specified on
		 * the command line.  If we can successfully read the
		 * TOC of a CD-ROM, use the last data track we find.
		 * Otherwise, just use 0, in order to mount the very
		 * first session.  This is compatible with the
		 * historic behaviour of mount_cd9660(8).  If the user
		 * has specified -s <ssector> above, we don't get here
		 * and leave the user's will.
		 */
		if ((ssector = get_ssector(dev)) == -1) {
			if (verbose)
				printf("could not determine starting sector, "
				       "using very first session\n");
			ssector = 0;
		} else if (verbose)
			printf("using starting sector %d\n", ssector);
	}
	mntflags |= MNT_RDONLY;
	build_iovec(&iov, &iovlen, "fstype", fstype, (size_t)-1);
	build_iovec(&iov, &iovlen, "fspath", mntpath, (size_t)-1);
	build_iovec(&iov, &iovlen, "from", dev, (size_t)-1);
	build_iovec_argf(&iov, &iovlen, "ssector", "%d", ssector);

	if (nmount(iov, iovlen, mntflags) < 0)
		err(1, "%s", dev);
	exit(0);
}