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
typedef  int off_t ;
typedef  int /*<<< orphan*/  fileargs_t ;
typedef  int /*<<< orphan*/  cap_rights_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_FCNTL ; 
 int /*<<< orphan*/  CAP_FSTAT ; 
 int /*<<< orphan*/  CAP_READ ; 
 int /*<<< orphan*/  FA_OPEN ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  cap_rights_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  caph_cache_catpages () ; 
 scalar_t__ caph_enter_casper () ; 
 scalar_t__ caph_limit_stdio () ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fileargs_fopen (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  fileargs_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fileargs_init (int,char**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int getopt_long (int,char**,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  head (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  head_bytes (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  long_opts ; 
 int /*<<< orphan*/  obsolete (char**) ; 
 int /*<<< orphan*/  optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  printf (char*,char*,char*) ; 
 int /*<<< orphan*/ * stdin ; 
 int strtoimax (int /*<<< orphan*/ ,char**,int) ; 
 int strtol (int /*<<< orphan*/ ,char**,int) ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  warn (char*,char*) ; 

int
main(int argc, char *argv[])
{
	FILE *fp;
	char *ep;
	off_t bytecnt;
	int ch, first, linecnt, eval;
	fileargs_t *fa;
	cap_rights_t rights;

	linecnt = -1;
	eval = 0;
	bytecnt = -1;

	obsolete(argv);
	while ((ch = getopt_long(argc, argv, "+n:c:", long_opts, NULL)) != -1) {
		switch(ch) {
		case 'c':
			bytecnt = strtoimax(optarg, &ep, 10);
			if (*ep || bytecnt <= 0)
				errx(1, "illegal byte count -- %s", optarg);
			break;
		case 'n':
			linecnt = strtol(optarg, &ep, 10);
			if (*ep || linecnt <= 0)
				errx(1, "illegal line count -- %s", optarg);
			break;
		case '?':
		default:
			usage();
			/* NOTREACHED */
		}
	}
	argc -= optind;
	argv += optind;

	fa = fileargs_init(argc, argv, O_RDONLY, 0,
	    cap_rights_init(&rights, CAP_READ, CAP_FSTAT, CAP_FCNTL), FA_OPEN);
	if (fa == NULL)
		err(1, "unable to init casper");

	caph_cache_catpages();
	if (caph_limit_stdio() < 0 || caph_enter_casper() < 0)
		err(1, "unable to enter capability mode");

	if (linecnt != -1 && bytecnt != -1)
		errx(1, "can't combine line and byte counts");
	if (linecnt == -1)
		linecnt = 10;
	if (*argv != NULL) {
		for (first = 1; *argv != NULL; ++argv) {
			if ((fp = fileargs_fopen(fa, *argv, "r")) == NULL) {
				warn("%s", *argv);
				eval = 1;
				continue;
			}
			if (argc > 1) {
				(void)printf("%s==> %s <==\n",
				    first ? "" : "\n", *argv);
				first = 0;
			}
			if (bytecnt == -1)
				head(fp, linecnt);
			else
				head_bytes(fp, bytecnt);
			(void)fclose(fp);
		}
	} else if (bytecnt == -1)
		head(stdin, linecnt);
	else
		head_bytes(stdin, bytecnt);

	fileargs_free(fa);
	exit(eval);
}