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
 int /*<<< orphan*/  SIGINT ; 
 scalar_t__ SIG_DFL ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int /*<<< orphan*/  _PATH_TMP ; 
 scalar_t__ cflg ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flushsh () ; 
 int /*<<< orphan*/ * freopen (char*,char*,int /*<<< orphan*/ ) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  ignore (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inithash () ; 
 int mkstemp (char*) ; 
 int /*<<< orphan*/  onintr ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  process (char*) ; 
 scalar_t__ readstd ; 
 scalar_t__ signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  stdout ; 
 char* strdup (int /*<<< orphan*/ ) ; 
 char* strings ; 
 int /*<<< orphan*/  unlink (char*) ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  vflg ; 
 int /*<<< orphan*/  xsdotc () ; 

int
main(int argc, char *argv[])
{
	int c;
	int fdesc;

	while ((c = getopt(argc, argv, "-cv")) != -1)
		switch (c) {
		case '-':
			readstd++;
			break;
		case 'c':
			cflg++;
			break;
		case 'v':
			vflg++;
			break;
		default:
			usage();
		}
	argc -= optind;
	argv += optind;
		
	if (signal(SIGINT, SIG_IGN) == SIG_DFL)
		signal(SIGINT, onintr);
	if (cflg || (argc == 0 && !readstd))
		inithash();
	else {
		strings = strdup(_PATH_TMP);
		if (strings == NULL)
			err(1, "strdup() failed");
		fdesc = mkstemp(strings);
		if (fdesc == -1)
			err(1, "Unable to create temporary file");
		close(fdesc);
	}

	while (readstd || argc > 0) {
		if (freopen("x.c", "w", stdout) == NULL)
			err(1, "x.c");
		if (!readstd && freopen(argv[0], "r", stdin) == NULL)
			err(2, "%s", argv[0]);
		process("x.c");
		if (readstd == 0)
			argc--, argv++;
		else
			readstd = 0;
	}
	flushsh();
	if (cflg == 0)
		xsdotc();
	if (strings[0] == '/')
		ignore(unlink(strings));
	exit(0);
}