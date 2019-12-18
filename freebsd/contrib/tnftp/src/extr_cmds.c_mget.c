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
struct stat {scalar_t__ st_size; } ;
typedef  int /*<<< orphan*/  sigfunc ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 size_t FEAT_REST_STREAM ; 
 int MAXPATHLEN ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  UPRINTF (char*,char*) ; 
 int /*<<< orphan*/  another (int*,char***,char*) ; 
 int code ; 
 scalar_t__ confirm (char*,char*) ; 
 int /*<<< orphan*/  connected ; 
 char* doprocess (char*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * features ; 
 int /*<<< orphan*/  fileindir (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ fromatty ; 
 int interactive ; 
 int /*<<< orphan*/  jabort ; 
 int /*<<< orphan*/  localcwd ; 
 int /*<<< orphan*/  mabort (char*) ; 
 int /*<<< orphan*/  mapflag ; 
 int /*<<< orphan*/  mcase ; 
 int mflag ; 
 int /*<<< orphan*/  mintr ; 
 int /*<<< orphan*/  ntflag ; 
 int /*<<< orphan*/  proxy ; 
 int /*<<< orphan*/  recvrequest (char*,char const*,char*,char*,int,int) ; 
 char* remglob (char**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ restart_point ; 
 scalar_t__ sigsetjmp (int /*<<< orphan*/ ,int) ; 
 scalar_t__ stat (char const*,struct stat*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  ttyout ; 
 int /*<<< orphan*/  warn (char*,char const*) ; 
 int /*<<< orphan*/  xsignal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
mget(int argc, char *argv[])
{
	sigfunc oldintr;
	int ointer;
	char *cp;
	const char *tp;
	int volatile restartit;

	if (argc == 0 ||
	    (argc == 1 && !another(&argc, &argv, "remote-files"))) {
		UPRINTF("usage: %s remote-files\n", argv[0]);
		code = -1;
		return;
	}
	mflag = 1;
	restart_point = 0;
	restartit = 0;
	if (strcmp(argv[0], "mreget") == 0) {
		if (! features[FEAT_REST_STREAM]) {
			fprintf(ttyout,
		    "Restart is not supported by the remote server.\n");
			return;
		}
		restartit = 1;
	}
	oldintr = xsignal(SIGINT, mintr);
	if (sigsetjmp(jabort, 1))
		mabort(argv[0]);
	while ((cp = remglob(argv, proxy, NULL)) != NULL) {
		char buf[MAXPATHLEN];
		if (*cp == '\0' || !connected) {
			mflag = 0;
			continue;
		}
		if (! mflag)
			continue;
		if (! fileindir(cp, localcwd)) {
			fprintf(ttyout, "Skipping non-relative filename `%s'\n",
			    cp);
			continue;
		}
		if (!confirm(argv[0], cp))
			continue;
		tp = doprocess(buf, sizeof(buf), cp, mcase, ntflag, mapflag);
		if (restartit) {
			struct stat stbuf;

			if (stat(tp, &stbuf) == 0)
				restart_point = stbuf.st_size;
			else
				warn("Can't stat `%s'", tp);
		}
		recvrequest("RETR", tp, cp, restart_point ? "r+" : "w",
		    tp != cp || !interactive, 1);
		restart_point = 0;
		if (!mflag && fromatty) {
			ointer = interactive;
			interactive = 1;
			if (confirm(argv[0], NULL))
				mflag++;
			interactive = ointer;
		}
	}
	(void)xsignal(SIGINT, oldintr);
	mflag = 0;
}