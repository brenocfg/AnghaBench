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
typedef  int /*<<< orphan*/  wchar_t ;

/* Variables and functions */
 int /*<<< orphan*/  LC_CTYPE ; 
 int /*<<< orphan*/ * delim ; 
 int delimcnt ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/ * malloc (size_t) ; 
 size_t mbsrtowcs (int /*<<< orphan*/ *,char const**,size_t,int /*<<< orphan*/ *) ; 
 char* optarg ; 
 scalar_t__ optind ; 
 int parallel (char**) ; 
 int sequential (char**) ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * tab ; 
 int tr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, char *argv[])
{
	int ch, rval, seq;
	wchar_t *warg;
	const char *arg;
	size_t len;

	setlocale(LC_CTYPE, "");

	seq = 0;
	while ((ch = getopt(argc, argv, "d:s")) != -1)
		switch(ch) {
		case 'd':
			arg = optarg;
			len = mbsrtowcs(NULL, &arg, 0, NULL);
			if (len == (size_t)-1)
				err(1, "delimiters");
			warg = malloc((len + 1) * sizeof(*warg));
			if (warg == NULL)
				err(1, NULL);
			arg = optarg;
			len = mbsrtowcs(warg, &arg, len + 1, NULL);
			if (len == (size_t)-1)
				err(1, "delimiters");
			delimcnt = tr(delim = warg);
			break;
		case 's':
			seq = 1;
			break;
		case '?':
		default:
			usage();
		}
	argc -= optind;
	argv += optind;

	if (*argv == NULL)
		usage();
	if (!delim) {
		delimcnt = 1;
		delim = tab;
	}

	if (seq)
		rval = sequential(argv);
	else
		rval = parallel(argv);
	exit(rval);
}