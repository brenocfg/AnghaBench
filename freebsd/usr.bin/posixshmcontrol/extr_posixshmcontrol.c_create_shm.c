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
 int create_one_shm (char*,long) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  optarg ; 
 scalar_t__ optind ; 
 long strtol (int /*<<< orphan*/ ,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage () ; 

__attribute__((used)) static int
create_shm(int argc, char **argv)
{
	char *end;
	long mode;
	int c, i, ret, ret1;

	mode = 0600;
	while ((c = getopt(argc, argv, "m:")) != -1) {
		switch (c) {
		case 'm':
			errno = 0;
			mode = strtol(optarg, &end, 0);
			if (mode == 0 && errno != 0)
				err(1, "mode:");
			if (*end != '\0')
				errx(1, "non-integer mode");
			break;
		case '?':
		default:
			usage();
			return (2);
		}
	}

	argc -= optind;
	argv += optind;
	ret = 0;
	for (i = 0; i < argc; i++) {
		ret1 = create_one_shm(argv[i], mode);
		if (ret1 != 0 && ret == 0)
			ret = ret1;
	}
	return (ret);
}