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
typedef  int /*<<< orphan*/  errmsg ;

/* Variables and functions */
 int EX_USAGE ; 
 int MAXPATHLEN ; 
 int /*<<< orphan*/  build_iovec (struct iovec**,int*,char*,char*,int) ; 
 scalar_t__ checkpath (char*,char*) ; 
 int /*<<< orphan*/  err (int,char*,char*,...) ; 
 int /*<<< orphan*/  errx (int,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int getopt (int,char**,char*) ; 
 scalar_t__ nmount (struct iovec*,int,int /*<<< orphan*/ ) ; 
 char* optarg ; 
 scalar_t__ optind ; 
 char* strchr (char*,char) ; 
 char* strdup (char*) ; 
 scalar_t__ subdir (char*,char*) ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, char *argv[])
{
	struct iovec *iov;
	char *p, *val;
	char source[MAXPATHLEN];
	char target[MAXPATHLEN];
	char errmsg[255];
	int ch, iovlen;
	char nullfs[] = "nullfs";

	iov = NULL;
	iovlen = 0;
	errmsg[0] = '\0';
	while ((ch = getopt(argc, argv, "o:")) != -1)
		switch(ch) {
		case 'o':
			val = strdup("");
			p = strchr(optarg, '=');
			if (p != NULL) {
				free(val);
				*p = '\0';
				val = p + 1;
			}
			build_iovec(&iov, &iovlen, optarg, val, (size_t)-1);
			break;
		case '?':
		default:
			usage();
		}
	argc -= optind;
	argv += optind;

	if (argc != 2)
		usage();

	/* resolve target and source with realpath(3) */
	if (checkpath(argv[0], target) != 0)
		err(EX_USAGE, "%s", target);
	if (checkpath(argv[1], source) != 0)
		err(EX_USAGE, "%s", source);

	if (subdir(target, source) || subdir(source, target))
		errx(EX_USAGE, "%s (%s) and %s are not distinct paths",
		    argv[0], target, argv[1]);

	build_iovec(&iov, &iovlen, "fstype", nullfs, (size_t)-1);
	build_iovec(&iov, &iovlen, "fspath", source, (size_t)-1);
	build_iovec(&iov, &iovlen, "target", target, (size_t)-1);
	build_iovec(&iov, &iovlen, "errmsg", errmsg, sizeof(errmsg));
	if (nmount(iov, iovlen, 0) < 0) {
		if (errmsg[0] != 0)
			err(1, "%s: %s", source, errmsg);
		else
			err(1, "%s", source);
	}
	exit(0);
}