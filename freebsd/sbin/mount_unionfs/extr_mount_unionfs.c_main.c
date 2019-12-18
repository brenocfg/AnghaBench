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
typedef  int /*<<< orphan*/  uid_str ;
struct iovec {int dummy; } ;
typedef  int /*<<< orphan*/  gid_str ;
typedef  int /*<<< orphan*/  errmsg ;

/* Variables and functions */
 int /*<<< orphan*/  EX_OSERR ; 
 int /*<<< orphan*/  EX_USAGE ; 
 int MAXPATHLEN ; 
 int /*<<< orphan*/  build_iovec (struct iovec**,int*,char*,char*,int) ; 
 scalar_t__ checkpath (char*,char*) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ nmount (struct iovec*,int,int /*<<< orphan*/ ) ; 
 char* optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  parse_gid (char*,char*,int) ; 
 int /*<<< orphan*/  parse_uid (char*,char*,int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 scalar_t__ subdir (char*,char*) ; 
 int /*<<< orphan*/  usage () ; 

int 
main(int argc, char *argv[])
{
	struct iovec	*iov;
	int ch, iovlen;
	char source [MAXPATHLEN], target[MAXPATHLEN], errmsg[255];
	char uid_str[20], gid_str[20];
	char fstype[] = "unionfs";
	char *p, *val;

	iov = NULL;
	iovlen = 0;
	memset(errmsg, 0, sizeof(errmsg));

	while ((ch = getopt(argc, argv, "bo:")) != -1) {
		switch (ch) {
		case 'b':
			printf("\n  -b is deprecated.  Use \"-o below\" instead\n");
			build_iovec(&iov, &iovlen, "below", NULL, 0);
			break;
		case 'o':
                        p = strchr(optarg, '=');
                        val = NULL;
                        if (p != NULL) {
                                *p = '\0';
                                val = p + 1;
				if (strcmp(optarg, "gid") == 0) {
					parse_gid(val, gid_str, sizeof(gid_str));
					val = gid_str;
				}
				else if (strcmp(optarg, "uid") == 0) {
					parse_uid(val, uid_str, sizeof(uid_str));
					val = uid_str;
				}
                        }
                        build_iovec(&iov, &iovlen, optarg, val, (size_t)-1);
			break;
		case '?':
		default:
			usage();
			/* NOTREACHED */
		}
	}
	argc -= optind;
	argv += optind;

	if (argc != 2)
		usage();

	/* resolve both target and source with realpath(3) */
	if (checkpath(argv[0], target) != 0)
		err(EX_USAGE, "%s", target);
	if (checkpath(argv[1], source) != 0)
		err(EX_USAGE, "%s", source);

	if (subdir(target, source) || subdir(source, target))
		errx(EX_USAGE, "%s (%s) and %s (%s) are not distinct paths",
		     argv[0], target, argv[1], source);

	build_iovec(&iov, &iovlen, "fstype", fstype, (size_t)-1);
	build_iovec(&iov, &iovlen, "fspath", source, (size_t)-1);
	build_iovec(&iov, &iovlen, "from", target, (size_t)-1);
	build_iovec(&iov, &iovlen, "errmsg", errmsg, sizeof(errmsg));

	if (nmount(iov, iovlen, 0))
		err(EX_OSERR, "%s: %s", source, errmsg);
	exit(0);
}