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
 int /*<<< orphan*/  Aflag ; 
 int Dflag ; 
 int /*<<< orphan*/  Hflag ; 
 scalar_t__ Lflag ; 
 int Nflag ; 
 int /*<<< orphan*/  Rflag ; 
 int aflag ; 
 int /*<<< orphan*/  append_variable (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  attrib ; 
 int /*<<< orphan*/  bflag ; 
 int /*<<< orphan*/  delete_variable (char*) ; 
 int /*<<< orphan*/  dflag ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  free (scalar_t__) ; 
 scalar_t__ fromfile ; 
 int getopt_long (int,char**,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gflag ; 
 int /*<<< orphan*/  lflag ; 
 int /*<<< orphan*/  load_opt_flag ; 
 int /*<<< orphan*/  longopts ; 
 char* optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  pflag ; 
 int /*<<< orphan*/  print_known_guid () ; 
 int /*<<< orphan*/  print_var (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_variable (char*) ; 
 int /*<<< orphan*/  print_variables () ; 
 scalar_t__ strdup (char*) ; 
 int /*<<< orphan*/  strtoul (char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  uflag ; 
 int /*<<< orphan*/  usage () ; 
 char* varname ; 
 int /*<<< orphan*/  warnx (char*) ; 
 int wflag ; 
 int /*<<< orphan*/  write_variable (char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
parse_args(int argc, char **argv)
{
	int ch, i;

	while ((ch = getopt_long(argc, argv, "aAbdDf:gHlLNn:OpRt:uw",
		    longopts, NULL)) != -1) {
		switch (ch) {
		case 'a':
			aflag++;
			break;
		case 'A':
			Aflag++;
			break;
		case 'b':
			bflag++;
			break;
		case 'd':
			dflag++;
			break;
		case 'D':
			Dflag++;
			break;
		case 'g':
			gflag++;
			break;
		case 'H':
			Hflag++;
			break;
		case 'l':
			lflag++;
			break;
		case 'L':
			Lflag++;
			break;
		case 'n':
			varname = optarg;
			break;
		case 'N':
			Nflag++;
			break;
		case 'O':
			load_opt_flag++;
			break;
		case 'p':
			pflag++;
			break;
		case 'R':
			Rflag++;
			break;
		case 't':
			attrib = strtoul(optarg, NULL, 16);
			break;
		case 'u':
			uflag++;
			break;
		case 'w':
			wflag++;
			break;
		case 'f':
			free(fromfile);
			fromfile = strdup(optarg);
			break;
		case 0:
			errx(1, "unknown or unimplemented option\n");
			break;
		default:
			usage();
		}
	}
	argc -= optind;
	argv += optind;

	if (argc == 1)
		varname = argv[0];

	if (aflag + Dflag + wflag > 1) {
		warnx("Can only use one of -a (--append), "
		    "-D (--delete) and -w (--write)");
		usage();
	}

	if (aflag + Dflag + wflag > 0 && varname == NULL) {
		warnx("Must specify a variable for -a (--append), "
		    "-D (--delete) or -w (--write)");
		usage();
	}

	if (aflag)
		append_variable(varname, NULL);
	else if (Dflag)
		delete_variable(varname);
	else if (wflag)
		write_variable(varname, NULL);
	else if (Lflag)
		print_known_guid();
	else if (fromfile) {
		Nflag = 1;
		print_var(NULL, NULL);
	} else if (varname) {
		pflag++;
		print_variable(varname);
	} else if (argc > 0) {
		pflag++;
		for (i = 0; i < argc; i++)
			print_variable(argv[i]);
	} else
		print_variables();
}