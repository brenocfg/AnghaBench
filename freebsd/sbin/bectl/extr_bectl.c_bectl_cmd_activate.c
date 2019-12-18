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
 int /*<<< orphan*/  be ; 
 int be_activate (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int getopt (int,char**,char*) ; 
 scalar_t__ optind ; 
 int optopt ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 int usage (int) ; 

__attribute__((used)) static int
bectl_cmd_activate(int argc, char *argv[])
{
	int err, opt;
	bool temp;

	temp = false;
	while ((opt = getopt(argc, argv, "t")) != -1) {
		switch (opt) {
		case 't':
			temp = true;
			break;
		default:
			fprintf(stderr, "bectl activate: unknown option '-%c'\n",
			    optopt);
			return (usage(false));
		}
	}

	argc -= optind;
	argv += optind;

	if (argc != 1) {
		fprintf(stderr, "bectl activate: wrong number of arguments\n");
		return (usage(false));
	}


	/* activate logic goes here */
	if ((err = be_activate(be, argv[0], temp)) != 0)
		/* XXX TODO: more specific error msg based on err */
		printf("did not successfully activate boot environment %s\n",
		    argv[0]);
	else
		printf("successfully activated boot environment %s\n", argv[0]);

	if (temp)
		printf("for next boot\n");

	return (err);
}