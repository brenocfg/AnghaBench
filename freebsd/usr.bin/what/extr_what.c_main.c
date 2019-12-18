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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int getopt (int,char**,char*) ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 scalar_t__ search (int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stdin ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  warn (char*,char const*) ; 

int
main(int argc, char *argv[])
{
	const char *file;
	FILE *in;
	bool found, qflag, sflag;
	int c;

	qflag = sflag = false;

	while ((c = getopt(argc, argv, "qs")) != -1) {
		switch (c) {
		case 'q':
			qflag = true;
			break;
		case 's':
			sflag = true;
			break;
		default:
			usage();
		}
	}
	argc -= optind;
	argv += optind;

	found = false;

	if (argc == 0) {
		if (search(sflag, qflag, stdin))
			found = true;
	} else {
		while (argc--) {
			file = *argv++;
			in = fopen(file, "r");
			if (in == NULL) {
				if (!qflag)
					warn("%s", file);
				continue;
			}
			if (!qflag)
				printf("%s:\n", file);
			if (search(sflag, qflag, in))
				found = true;
			fclose(in);
		}
	}
	exit(found ? 0 : 1);
}