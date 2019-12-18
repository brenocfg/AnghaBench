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
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int getopt (int,char**,char*) ; 
 int openpam_debug ; 
 int /*<<< orphan*/  openpam_dump_policy (char*) ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, char *argv[])
{
	int i, opt;

	while ((opt = getopt(argc, argv, "d")) != -1)
		switch (opt) {
		case 'd':
			openpam_debug = 1;
			break;
		default:
			usage();
		}

	argc -= optind;
	argv += optind;

	if (argc < 1)
		usage();

	printf("#include <security/pam_appl.h>\n");
	printf("#include \"openpam_impl.h\"\n");
	for (i = 0; i < argc; ++i)
		openpam_dump_policy(argv[i]);
	printf("pam_policy_t *pam_embedded_policies[] = {\n");
	for (i = 0; i < argc; ++i)
		printf("\t&pam_%s_policy,\n", argv[i]);
	printf("\tNULL,\n");
	printf("};\n");
	exit(0);
}