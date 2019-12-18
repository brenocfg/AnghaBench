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
struct mparse {int dummy; } ;

/* Variables and functions */
 scalar_t__ MANDOCLEVEL_BADARG ; 
 scalar_t__ MANDOCLEVEL_OK ; 
 int /*<<< orphan*/  MANDOC_OS_OTHER ; 
 int MPARSE_LATIN1 ; 
 int MPARSE_SO ; 
 int MPARSE_UTF8 ; 
 int MPARSE_VALIDATE ; 
 int STDIN_FILENO ; 
 int /*<<< orphan*/  assert (struct mparse*) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  mchars_alloc () ; 
 int /*<<< orphan*/  mchars_free () ; 
 struct mparse* mparse_alloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mparse_free (struct mparse*) ; 
 int mparse_open (struct mparse*,char*) ; 
 int /*<<< orphan*/  mparse_reset (struct mparse*) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  pmandoc (struct mparse*,int,char*,int) ; 
 char* progname ; 
 char* strrchr (char*,char) ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, char *argv[])
{
	struct mparse	*mp;
	int		 ch, fd, i, list;
	extern int	 optind;

	if (argc < 1)
		progname = "demandoc";
	else if ((progname = strrchr(argv[0], '/')) == NULL)
		progname = argv[0];
	else
		++progname;

	mp = NULL;
	list = 0;

	while (-1 != (ch = getopt(argc, argv, "ikm:pw")))
		switch (ch) {
		case ('i'):
			/* FALLTHROUGH */
		case ('k'):
			/* FALLTHROUGH */
		case ('m'):
			/* FALLTHROUGH */
		case ('p'):
			break;
		case ('w'):
			list = 1;
			break;
		default:
			usage();
			return (int)MANDOCLEVEL_BADARG;
		}

	argc -= optind;
	argv += optind;

	mchars_alloc();
	mp = mparse_alloc(MPARSE_SO | MPARSE_UTF8 | MPARSE_LATIN1 |
	    MPARSE_VALIDATE, MANDOC_OS_OTHER, NULL);
	assert(mp);

	if (argc < 1)
		pmandoc(mp, STDIN_FILENO, "<stdin>", list);

	for (i = 0; i < argc; i++) {
		mparse_reset(mp);
		if ((fd = mparse_open(mp, argv[i])) == -1) {
			perror(argv[i]);
			continue;
		}
		pmandoc(mp, fd, argv[i], list);
	}

	mparse_free(mp);
	mchars_free();
	return (int)MANDOCLEVEL_OK;
}