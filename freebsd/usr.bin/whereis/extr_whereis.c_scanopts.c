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
typedef  int /*<<< orphan*/ * ccharp ;

/* Variables and functions */
 int /*<<< orphan*/ ** bindirs ; 
 int /*<<< orphan*/  decolonify (char*,int /*<<< orphan*/ ***,int*) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/ ** mandirs ; 
 int opt_a ; 
 int opt_b ; 
 int opt_m ; 
 int opt_q ; 
 int opt_s ; 
 int opt_u ; 
 int opt_x ; 
 int optind ; 
 char** query ; 
 int /*<<< orphan*/ ** realloc (int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/ ** sourcedirs ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  usage () ; 

__attribute__((used)) static void
scanopts(int argc, char **argv)
{
	int c, i;
	ccharp **dirlist;

	while ((c = getopt(argc, argv, "BMSabfmqsux")) != -1)
		switch (c) {
		case 'B':
			dirlist = &bindirs;
			goto dolist;

		case 'M':
			dirlist = &mandirs;
			goto dolist;

		case 'S':
			dirlist = &sourcedirs;
		  dolist:
			i = 0;
			*dirlist = realloc(*dirlist, (i + 1) * sizeof(char *));
			(*dirlist)[i] = NULL;
			while (optind < argc &&
			       strcmp(argv[optind], "-f") != 0 &&
			       strcmp(argv[optind], "-B") != 0 &&
			       strcmp(argv[optind], "-M") != 0 &&
			       strcmp(argv[optind], "-S") != 0) {
				decolonify(argv[optind], dirlist, &i);
				optind++;
			}
			break;

		case 'a':
			opt_a = 1;
			break;

		case 'b':
			opt_b = 1;
			break;

		case 'f':
			goto breakout;

		case 'm':
			opt_m = 1;
			break;

		case 'q':
			opt_q = 1;
			break;

		case 's':
			opt_s = 1;
			break;

		case 'u':
			opt_u = 1;
			break;

		case 'x':
			opt_x = 1;
			break;

		default:
			usage();
		}
  breakout:
	if (optind == argc)
		usage();
	query = argv + optind;
}