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
 int /*<<< orphan*/  LC_ALL ; 
 char* basename (char*) ; 
 scalar_t__ caph_enter () ; 
 scalar_t__ caph_limit_stdio () ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int getopt (int,char**,char*) ; 
 char* optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stripsuffix (char*,char*,size_t) ; 
 size_t strlen (char*) ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, char **argv)
{
	char *p, *suffix;
	size_t suffixlen;
	int aflag, ch;

	setlocale(LC_ALL, "");

	if (caph_limit_stdio() < 0 || caph_enter() < 0)
		err(1, "capsicum");

	aflag = 0;
	suffix = NULL;
	suffixlen = 0;

	while ((ch = getopt(argc, argv, "as:")) != -1)
		switch(ch) {
		case 'a':
			aflag = 1;
			break;
		case 's':
			suffix = optarg;
			break;
		case '?':
		default:
			usage();
		}
	argc -= optind;
	argv += optind;

	if (argc < 1)
		usage();

	if (!*argv[0]) {
		printf("\n");
		exit(0);
	}
	if ((p = basename(argv[0])) == NULL)
		err(1, "%s", argv[0]);
	if ((suffix == NULL && !aflag) && argc == 2) {
		suffix = argv[1];
		argc--;
	}
	if (suffix != NULL)
		suffixlen = strlen(suffix);
	while (argc--) {
		if ((p = basename(*argv)) == NULL)
			err(1, "%s", argv[0]);
		stripsuffix(p, suffix, suffixlen);
		argv++;
		(void)printf("%s\n", p);
	}
	exit(0);
}