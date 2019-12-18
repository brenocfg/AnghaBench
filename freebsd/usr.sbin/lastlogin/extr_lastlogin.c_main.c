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
struct utmpx {scalar_t__ ut_type; } ;

/* Variables and functions */
 scalar_t__ USER_PROCESS ; 
 int /*<<< orphan*/  UTXDB_LASTLOGIN ; 
 int /*<<< orphan*/  endutxent () ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  file ; 
 int getopt (int,char**,char*) ; 
 struct utmpx* getutxent () ; 
 struct utmpx* getutxuser (char*) ; 
 int /*<<< orphan*/  optarg ; 
 scalar_t__ optind ; 
 int order ; 
 int /*<<< orphan*/  output (struct utmpx*) ; 
 int /*<<< orphan*/  qsort (struct utmpx*,int,int,int /*<<< orphan*/ ) ; 
 struct utmpx* realloc (struct utmpx*,int) ; 
 scalar_t__ setutxdb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  utcmp ; 
 int /*<<< orphan*/  utcmp_time ; 
 int /*<<< orphan*/  xo_close_container (char*) ; 
 int /*<<< orphan*/  xo_close_list (char*) ; 
 int /*<<< orphan*/  xo_err (int,char*) ; 
 int /*<<< orphan*/  xo_finish () ; 
 int /*<<< orphan*/  xo_open_container (char*) ; 
 int /*<<< orphan*/  xo_open_list (char*) ; 
 int xo_parse_args (int,char**) ; 
 int /*<<< orphan*/  xo_warnx (char*,char*) ; 

int
main(int argc, char *argv[])
{
	int	ch, i, ulistsize;
	struct utmpx *u, *ulist;

	argc = xo_parse_args(argc, argv);
	if (argc < 0)
		exit(1);

	while ((ch = getopt(argc, argv, "f:rt")) != -1) {
		switch (ch) {
		case 'f':
			file = optarg;
			break;
		case 'r':
			order = -1;
			break;
		case 't':
			utcmp = utcmp_time;
			break;
		default:
			usage();
		}
	}
	argc -= optind;
	argv += optind;

	xo_open_container("lastlogin-information");
	xo_open_list("lastlogin");

	if (argc > 0) {
		/* Process usernames given on the command line. */
		for (i = 0; i < argc; i++) {
			if (setutxdb(UTXDB_LASTLOGIN, file) != 0)
				xo_err(1, "failed to open lastlog database");
			if ((u = getutxuser(argv[i])) == NULL) {
				xo_warnx("user '%s' not found", argv[i]);
				continue;
			}
			output(u);
			endutxent();
		}
	} else {
		/* Read all lastlog entries, looking for active ones. */
		if (setutxdb(UTXDB_LASTLOGIN, file) != 0)
			xo_err(1, "failed to open lastlog database");
		ulist = NULL;
		ulistsize = 0;
		while ((u = getutxent()) != NULL) {
			if (u->ut_type != USER_PROCESS)
				continue;
			if ((ulistsize % 16) == 0) {
				ulist = realloc(ulist,
				    (ulistsize + 16) * sizeof(struct utmpx));
				if (ulist == NULL)
					xo_err(1, "malloc");
			}
			ulist[ulistsize++] = *u;
		}
		endutxent();

		qsort(ulist, ulistsize, sizeof(struct utmpx), utcmp);
		for (i = 0; i < ulistsize; i++)
			output(&ulist[i]);
	}

	xo_close_list("lastlogin");
	xo_close_container("lastlogin-information");
	xo_finish();

	exit(0);
}