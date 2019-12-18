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
#define  BE_ERR_SUCCESS 128 
 int BE_MNT_FORCE ; 
 int /*<<< orphan*/  be ; 
 int be_unmount (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,...) ; 
 int getopt (int,char**,char*) ; 
 scalar_t__ optind ; 
 int optopt ; 
 int /*<<< orphan*/  stderr ; 
 int usage (int) ; 

__attribute__((used)) static int
bectl_cmd_unmount(int argc, char *argv[])
{
	char *bootenv, *cmd;
	int err, flags, opt;

	/* Store alias used */
	cmd = argv[0];

	flags = 0;
	while ((opt = getopt(argc, argv, "f")) != -1) {
		switch (opt) {
		case 'f':
			flags |= BE_MNT_FORCE;
			break;
		default:
			fprintf(stderr, "bectl %s: unknown option '-%c'\n",
			    cmd, optopt);
			return (usage(false));
		}
	}

	argc -= optind;
	argv += optind;

	if (argc != 1) {
		fprintf(stderr, "bectl %s: wrong number of arguments\n", cmd);
		return (usage(false));
	}

	bootenv = argv[0];

	err = be_unmount(be, bootenv, flags);

	switch (err) {
	case BE_ERR_SUCCESS:
		break;
	default:
		fprintf(stderr, "failed to unmount bootenv %s\n", bootenv);
	}

	return (err);
}