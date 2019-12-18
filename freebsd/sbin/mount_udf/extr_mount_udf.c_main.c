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
typedef  int /*<<< orphan*/  udf_flags ;
struct iovec {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EX_OSERR ; 
 int EX_USAGE ; 
 int MAXPATHLEN ; 
 int MNT_RDONLY ; 
 int UDFMNT_KICONV ; 
 int /*<<< orphan*/  build_iovec (struct iovec**,int*,char*,...) ; 
 scalar_t__ checkpath (char*,char*) ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getmntopts (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  mopts ; 
 scalar_t__ nmount (struct iovec*,int,int) ; 
 int /*<<< orphan*/  optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  rmslashes (char*,char*) ; 
 int set_charset (char**,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, char **argv)
{
	char mntpath[MAXPATHLEN];
	char fstype[] = "udf";
	struct iovec *iov;
	char *cs_disk, *cs_local, *dev, *dir;
	int ch, iovlen, mntflags, udf_flags, verbose;

	iovlen = mntflags = udf_flags = verbose = 0;
	cs_disk = cs_local = NULL;
	iov = NULL;
	while ((ch = getopt(argc, argv, "o:vC:")) != -1)
		switch (ch) {
		case 'o':
			getmntopts(optarg, mopts, &mntflags, NULL);
			break;
		case 'v':
			verbose++;
			break;
		case 'C':
			if (set_charset(&cs_disk, &cs_local, optarg) == -1)
				err(EX_OSERR, "udf_iconv");
			udf_flags |= UDFMNT_KICONV;
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
		err(EX_USAGE, "%s", mntpath);
	(void)rmslashes(dev, dev);

	/*
	 * UDF file systems are not writeable.
	 */
	mntflags |= MNT_RDONLY;

	build_iovec(&iov, &iovlen, "fstype", fstype, (size_t)-1);
	build_iovec(&iov, &iovlen, "fspath", mntpath, (size_t)-1);
	build_iovec(&iov, &iovlen, "from", dev, (size_t)-1);
	build_iovec(&iov, &iovlen, "flags", &udf_flags, sizeof(udf_flags));
	if (udf_flags & UDFMNT_KICONV) {
		build_iovec(&iov, &iovlen, "cs_disk", cs_disk, (size_t)-1);
		build_iovec(&iov, &iovlen, "cs_local", cs_local, (size_t)-1);
	}
	if (nmount(iov, iovlen, mntflags) < 0)
		err(1, "%s", dev);
	exit(0);
}