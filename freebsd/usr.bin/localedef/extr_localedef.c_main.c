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
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  LC_ALL ; 
 int /*<<< orphan*/  add_charmap_posix () ; 
 int bsd ; 
 int byteorder ; 
 int /*<<< orphan*/  category_file () ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 char* dirname (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errf (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  init_charmap () ; 
 int /*<<< orphan*/  init_collate () ; 
 int /*<<< orphan*/  init_ctype () ; 
 int /*<<< orphan*/  init_messages () ; 
 int /*<<< orphan*/  init_monetary () ; 
 int /*<<< orphan*/  init_numeric () ; 
 int /*<<< orphan*/  init_time () ; 
 char* locname ; 
 scalar_t__ mkdir (char*,int) ; 
 int /*<<< orphan*/ * opendir (char*) ; 
 char* optarg ; 
 int optind ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  reset_scanner (char*) ; 
 int /*<<< orphan*/  set_wide_encoding (char*) ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 
 int /*<<< orphan*/  undefok ; 
 int /*<<< orphan*/  usage () ; 
 scalar_t__ verbose ; 
 scalar_t__ warnings ; 
 int /*<<< orphan*/  warnok ; 
 scalar_t__ yydebug ; 
 int /*<<< orphan*/  yyparse () ; 

int
main(int argc, char **argv)
{
	int c;
	char *lfname = NULL;
	char *cfname = NULL;
	char *wfname = NULL;
	DIR *dir;

	init_charmap();
	init_collate();
	init_ctype();
	init_messages();
	init_monetary();
	init_numeric();
	init_time();

	yydebug = 0;

	(void) setlocale(LC_ALL, "");

	while ((c = getopt(argc, argv, "blw:i:cf:u:vUD")) != -1) {
		switch (c) {
		case 'D':
			bsd = 1;
			break;
		case 'b':
		case 'l':
			if (byteorder != 0)
				usage();
			byteorder = c == 'b' ? 4321 : 1234;
			break;
		case 'v':
			verbose++;
			break;
		case 'i':
			lfname = optarg;
			break;
		case 'u':
			set_wide_encoding(optarg);
			break;
		case 'f':
			cfname = optarg;
			break;
		case 'U':
			undefok++;
			break;
		case 'c':
			warnok++;
			break;
		case 'w':
			wfname = optarg;
			break;
		case '?':
			usage();
			break;
		}
	}

	if ((argc - 1) != (optind)) {
		usage();
	}
	locname = argv[argc - 1];
	if (verbose) {
		(void) printf("Processing locale %s.\n", locname);
	}

	if (cfname) {
		if (verbose)
			(void) printf("Loading charmap %s.\n", cfname);
		reset_scanner(cfname);
		(void) yyparse();
	}

	if (wfname) {
		if (verbose)
			(void) printf("Loading widths %s.\n", wfname);
		reset_scanner(wfname);
		(void) yyparse();
	}

	if (verbose) {
		(void) printf("Loading POSIX portable characters.\n");
	}
	add_charmap_posix();

	if (lfname) {
		reset_scanner(lfname);
	} else {
		reset_scanner(NULL);
	}

	/* make the directory for the locale if not already present */
	if (!bsd) {
		while ((dir = opendir(locname)) == NULL) {
			if ((errno != ENOENT) ||
			    (mkdir(locname, 0755) <  0)) {
				errf("%s", strerror(errno));
			}
		}
		(void) closedir(dir);
		(void) mkdir(dirname(category_file()), 0755);
	}

	(void) yyparse();
	if (verbose) {
		(void) printf("All done.\n");
	}
	return (warnings ? 1 : 0);
}