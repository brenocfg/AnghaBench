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
typedef  int /*<<< orphan*/  sigfunc ;

/* Variables and functions */
 scalar_t__ COMPLETE ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  UPRINTF (char*,char*) ; 
 int /*<<< orphan*/  another (int*,char***,char*) ; 
 int code ; 
 scalar_t__ command (char*,char*) ; 
 scalar_t__ confirm (char*,char*) ; 
 int dirchange ; 
 scalar_t__ fromatty ; 
 int interactive ; 
 int /*<<< orphan*/  jabort ; 
 int /*<<< orphan*/  mabort (char*) ; 
 int mflag ; 
 int /*<<< orphan*/  mintr ; 
 char* remglob (char**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ sigsetjmp (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xsignal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
mdelete(int argc, char *argv[])
{
	sigfunc oldintr;
	int ointer;
	char *cp;

	if (argc == 0 ||
	    (argc == 1 && !another(&argc, &argv, "remote-files"))) {
		UPRINTF("usage: %s [remote-files]\n", argv[0]);
		code = -1;
		return;
	}
	mflag = 1;
	oldintr = xsignal(SIGINT, mintr);
	if (sigsetjmp(jabort, 1))
		mabort(argv[0]);
	while ((cp = remglob(argv, 0, NULL)) != NULL) {
		if (*cp == '\0') {
			mflag = 0;
			continue;
		}
		if (mflag && confirm(argv[0], cp)) {
			if (command("DELE %s", cp) == COMPLETE)
				dirchange = 1;
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
	(void)xsignal(SIGINT, oldintr);
	mflag = 0;
}