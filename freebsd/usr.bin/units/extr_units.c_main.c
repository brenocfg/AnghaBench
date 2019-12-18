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
struct unittype {int dummy; } ;
typedef  int /*<<< orphan*/  History ;
typedef  int /*<<< orphan*/  HistEvent ;
typedef  int /*<<< orphan*/  EditLine ;

/* Variables and functions */
 int /*<<< orphan*/  EL_EDITOR ; 
 int /*<<< orphan*/  EL_HIST ; 
 int /*<<< orphan*/  EL_PROMPT ; 
 int /*<<< orphan*/  EL_SIGNAL ; 
 int /*<<< orphan*/  F_OK ; 
 int /*<<< orphan*/  H_ENTER ; 
 int /*<<< orphan*/  H_SETSIZE ; 
 char* UNITSFILE ; 
 int /*<<< orphan*/  access (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ addunit (struct unittype*,char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ caph_enter () ; 
 scalar_t__ completereduce (struct unittype*) ; 
 int /*<<< orphan*/  el_end (int /*<<< orphan*/ *) ; 
 char* el_gets (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/ * el_init (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  el_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  el_source (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int getopt_long (int,char**,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* havestr ; 
 int /*<<< orphan*/  history (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  history_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * history_init () ; 
 int /*<<< orphan*/  initializeunit (struct unittype*) ; 
 int /*<<< orphan*/  longopts ; 
 char* numfmt ; 
 char* optarg ; 
 int optind ; 
 char* outputformat ; 
 int prefixcount ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  prompt ; 
 char* promptstr ; 
 int /*<<< orphan*/  readunits (char*) ; 
 int /*<<< orphan*/  showanswer (struct unittype*,struct unittype*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int terse ; 
 int unitcount ; 
 int /*<<< orphan*/  usage () ; 
 int verbose ; 
 char* wantstr ; 

int
main(int argc, char **argv)
{

	struct unittype have, want;
	int optchar;
	bool quiet;
	bool readfile;
	bool quit;
	History *inhistory;
	EditLine *el;
	HistEvent ev;
	int inputsz;
	char const * history_file;

	quiet = false;
	readfile = false;
	history_file = NULL;
	outputformat = numfmt;
	quit = false;
	while ((optchar = getopt_long(argc, argv, "+ehf:o:qtvH:UV", longopts, NULL)) != -1) {
		switch (optchar) {
		case 'e':
			outputformat = "%6e";
			break;
		case 'f':
			readfile = true;
			if (strlen(optarg) == 0)
				readunits(NULL);
			else
				readunits(optarg);
			break;
		case 'H':
			history_file = optarg;
			break;
		case 'q':
			quiet = true;
			break;
		case 't':
			terse = true;
			break;
		case 'o':
			outputformat = optarg;
			break;
		case 'v':
			verbose = true;
			break;
		case 'V':
			fprintf(stderr, "FreeBSD units\n");
			/* FALLTHROUGH */
		case 'U':
			if (access(UNITSFILE, F_OK) == 0)
				printf("%s\n", UNITSFILE);
			else
				printf("Units data file not found");
			exit(0);
		case 'h':
			/* FALLTHROUGH */

		default:
			usage();
		}
	}

	if (!readfile)
		readunits(NULL);

	if (optind == argc - 2) {
		if (caph_enter() < 0)
			err(1, "unable to enter capability mode");

		havestr = argv[optind];
		wantstr = argv[optind + 1];
		initializeunit(&have);
		addunit(&have, havestr, 0, 1);
		completereduce(&have);
		initializeunit(&want);
		addunit(&want, wantstr, 0, 1);
		completereduce(&want);
		showanswer(&have, &want);
	} else {
		inhistory = history_init();
		el = el_init(argv[0], stdin, stdout, stderr);
		el_set(el, EL_PROMPT, &prompt);
		el_set(el, EL_EDITOR, "emacs");
		el_set(el, EL_SIGNAL, 1);
		el_set(el, EL_HIST, history, inhistory);
		el_source(el, NULL);
		history(inhistory, &ev, H_SETSIZE, 800);
		if (inhistory == 0)
			err(1, "Could not initialize history");

		if (caph_enter() < 0)
			err(1, "unable to enter capability mode");

		if (!quiet)
			printf("%d units, %d prefixes\n", unitcount,
			    prefixcount);
		while (!quit) {
			do {
				initializeunit(&have);
				if (!quiet)
					promptstr = "You have: ";
				havestr = el_gets(el, &inputsz);
				if (havestr == NULL) {
					quit = true;
					break;
				}
				if (inputsz > 0)
					history(inhistory, &ev, H_ENTER,
					havestr);
			} while (addunit(&have, havestr, 0, 1) ||
			    completereduce(&have));
			if (quit) {
				break;
			}
			do {
				initializeunit(&want);
				if (!quiet)
					promptstr = "You want: ";
				wantstr = el_gets(el, &inputsz);
				if (wantstr == NULL) {
					quit = true;
					break;
				}
				if (inputsz > 0)
					history(inhistory, &ev, H_ENTER,
					wantstr);
			} while (addunit(&want, wantstr, 0, 1) ||
			    completereduce(&want));
			if (quit) {
				break;
			}
			showanswer(&have, &want);
		}

		history_end(inhistory);
		el_end(el);
	}

	return (0);
}