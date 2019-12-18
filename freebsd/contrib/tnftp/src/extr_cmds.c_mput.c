#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sigfunc ;
struct TYPE_5__ {scalar_t__ gl_pathc; char** gl_pathv; } ;
typedef  TYPE_1__ glob_t ;
typedef  int /*<<< orphan*/  gl ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int GLOB_BRACE ; 
 int GLOB_NOCHECK ; 
 int GLOB_TILDE ; 
 int MAXPATHLEN ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  UPRINTF (char*,char*) ; 
 int /*<<< orphan*/  another (int*,char***,char*) ; 
 int code ; 
 scalar_t__ confirm (char*,char*) ; 
 scalar_t__ connected ; 
 int /*<<< orphan*/  doglob ; 
 char* doprocess (char*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ fromatty ; 
 scalar_t__ glob (char*,int,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  globfree (TYPE_1__*) ; 
 int interactive ; 
 int /*<<< orphan*/  jabort ; 
 int /*<<< orphan*/  mabort (char*) ; 
 int /*<<< orphan*/  mapflag ; 
 int /*<<< orphan*/  mcase ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int mflag ; 
 int /*<<< orphan*/  mintr ; 
 int /*<<< orphan*/  ntflag ; 
 scalar_t__ proxy ; 
 char* remglob (char**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sendrequest (char*,char*,char const*,int) ; 
 scalar_t__ sigsetjmp (int /*<<< orphan*/ ,int) ; 
 scalar_t__ sunique ; 
 int /*<<< orphan*/  warnx (char*,char*) ; 
 int /*<<< orphan*/  xsignal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
mput(int argc, char *argv[])
{
	int i;
	sigfunc oldintr;
	int ointer;
	const char *tp;

	if (argc == 0 || (argc == 1 && !another(&argc, &argv, "local-files"))) {
		UPRINTF("usage: %s local-files\n", argv[0]);
		code = -1;
		return;
	}
	mflag = 1;
	oldintr = xsignal(SIGINT, mintr);
	if (sigsetjmp(jabort, 1))
		mabort(argv[0]);
	if (proxy) {
		char *cp;

		while ((cp = remglob(argv, 0, NULL)) != NULL) {
			if (*cp == '\0' || !connected) {
				mflag = 0;
				continue;
			}
			if (mflag && confirm(argv[0], cp)) {
				char buf[MAXPATHLEN];
				tp = doprocess(buf, sizeof(buf), cp,
				    mcase, ntflag, mapflag);
				sendrequest((sunique) ? "STOU" : "STOR",
				    cp, tp, cp != tp || !interactive);
				if (!mflag && fromatty) {
					ointer = interactive;
					interactive = 1;
					if (confirm(argv[0], NULL)) {
						mflag++;
					}
					interactive = ointer;
				}
			}
		}
		goto cleanupmput;
	}
	for (i = 1; i < argc && connected; i++) {
		char **cpp;
		glob_t gl;
		int flags;

		if (!doglob) {
			if (mflag && confirm(argv[0], argv[i])) {
				char buf[MAXPATHLEN];
				tp = doprocess(buf, sizeof(buf), argv[i],
					0, ntflag, mapflag);
				sendrequest((sunique) ? "STOU" : "STOR",
				    argv[i], tp, tp != argv[i] || !interactive);
				if (!mflag && fromatty) {
					ointer = interactive;
					interactive = 1;
					if (confirm(argv[0], NULL)) {
						mflag++;
					}
					interactive = ointer;
				}
			}
			continue;
		}

		memset(&gl, 0, sizeof(gl));
		flags = GLOB_BRACE|GLOB_NOCHECK|GLOB_TILDE;
		if (glob(argv[i], flags, NULL, &gl) || gl.gl_pathc == 0) {
			warnx("Glob pattern `%s' not found", argv[i]);
			globfree(&gl);
			continue;
		}
		for (cpp = gl.gl_pathv; cpp && *cpp != NULL && connected;
		    cpp++) {
			if (mflag && confirm(argv[0], *cpp)) {
				char buf[MAXPATHLEN];
				tp = *cpp;
				tp = doprocess(buf, sizeof(buf), *cpp,
				    0, ntflag, mapflag);
				sendrequest((sunique) ? "STOU" : "STOR",
				    *cpp, tp, *cpp != tp || !interactive);
				if (!mflag && fromatty) {
					ointer = interactive;
					interactive = 1;
					if (confirm(argv[0], NULL)) {
						mflag++;
					}
					interactive = ointer;
				}
			}
		}
		globfree(&gl);
	}
 cleanupmput:
	(void)xsignal(SIGINT, oldintr);
	mflag = 0;
}