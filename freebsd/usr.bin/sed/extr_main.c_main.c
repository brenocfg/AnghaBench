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
 int /*<<< orphan*/  CU_FILE ; 
 int /*<<< orphan*/  CU_STRING ; 
 int /*<<< orphan*/  LC_ALL ; 
 int /*<<< orphan*/  REG_EXTENDED ; 
 int /*<<< orphan*/  _IOLBF ; 
 int /*<<< orphan*/  _IONBF ; 
 int /*<<< orphan*/  add_compunit (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  add_file (char*) ; 
 int aflag ; 
 int /*<<< orphan*/  cfclose (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  compile () ; 
 int eflag ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 scalar_t__ fclose (int /*<<< orphan*/ ) ; 
 int getopt (int,char**,char*) ; 
 char* inplace ; 
 int ispan ; 
 char* malloc (int /*<<< orphan*/ ) ; 
 int nflag ; 
 char* optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  process () ; 
 int /*<<< orphan*/  prog ; 
 int /*<<< orphan*/  rflags ; 
 int /*<<< orphan*/  rval ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  setvbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  warnx (char*) ; 

int
main(int argc, char *argv[])
{
	int c, fflag;
	char *temp_arg;

	(void) setlocale(LC_ALL, "");

	fflag = 0;
	inplace = NULL;

	while ((c = getopt(argc, argv, "EI:ae:f:i:lnru")) != -1)
		switch (c) {
		case 'r':		/* Gnu sed compat */
		case 'E':
			rflags = REG_EXTENDED;
			break;
		case 'I':
			inplace = optarg;
			ispan = 1;	/* span across input files */
			break;
		case 'a':
			aflag = 1;
			break;
		case 'e':
			eflag = 1;
			if ((temp_arg = malloc(strlen(optarg) + 2)) == NULL)
				err(1, "malloc");
			strcpy(temp_arg, optarg);
			strcat(temp_arg, "\n");
			add_compunit(CU_STRING, temp_arg);
			break;
		case 'f':
			fflag = 1;
			add_compunit(CU_FILE, optarg);
			break;
		case 'i':
			inplace = optarg;
			ispan = 0;	/* don't span across input files */
			break;
		case 'l':
			if(setvbuf(stdout, NULL, _IOLBF, 0) != 0)
				warnx("setting line buffered output failed");
			break;
		case 'n':
			nflag = 1;
			break;
		case 'u':
			if(setvbuf(stdout, NULL, _IONBF, 0) != 0)
				warnx("setting unbuffered output failed");
			break;
		default:
		case '?':
			usage();
		}
	argc -= optind;
	argv += optind;

	/* First usage case; script is the first arg */
	if (!eflag && !fflag && *argv) {
		add_compunit(CU_STRING, *argv);
		argv++;
	}

	compile();

	/* Continue with first and start second usage */
	if (*argv)
		for (; *argv; argv++)
			add_file(*argv);
	else
		add_file(NULL);
	process();
	cfclose(prog, NULL);
	if (fclose(stdout))
		err(1, "stdout");
	exit(rval);
}