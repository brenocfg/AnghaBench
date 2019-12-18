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
typedef  int /*<<< orphan*/  line ;

/* Variables and functions */
 int /*<<< orphan*/  convert (char*) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ ) ; 
 int getopt (int,char**,char*) ; 
 int lflag ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/ * strchr (char*,char) ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, char *argv[])
{
	int ch, first;
	char line[256];

	lflag = 0;
	while ((ch = getopt(argc, argv, "l")) != -1)
		switch (ch) {
		case 'l':
			lflag = 1;
			break;
		case '?':
		default:
			usage();
		}
	argc -= optind;
	argv += optind;

	if (*argv == NULL)
		for (first = 1;
		    fgets(line, sizeof(line), stdin) != NULL; first = 0) {
			if (strchr(line, '\n') == NULL)
				errx(1, "line too long.");
			if (!first)
				(void)printf("...\n");
			convert(line);
		}
	else
		for (first = 1; *argv != NULL; first = 0, ++argv) {
			if (!first)
				(void)printf("...\n");
			convert(*argv);
		}
	exit(0);
}