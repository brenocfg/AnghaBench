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
typedef  int /*<<< orphan*/  sighand ;

/* Variables and functions */
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  another (int*,char***,char*) ; 
 int code ; 
 int /*<<< orphan*/  command (char*,char*) ; 
 scalar_t__ confirm (char*,char*) ; 
 scalar_t__ fromatty ; 
 int interactive ; 
 int /*<<< orphan*/  jabort ; 
 int /*<<< orphan*/  mabort ; 
 int mflag ; 
 char* mname ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 char* remglob (char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setjmp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
mdelete(int argc, char **argv)
{
    sighand oldintr;
    int ointer;
    char *cp;

    if (argc < 2 && !another(&argc, &argv, "remote-files")) {
	printf("usage: %s remote-files\n", argv[0]);
	code = -1;
	return;
    }
    mname = argv[0];
    mflag = 1;
    oldintr = signal(SIGINT, mabort);
    setjmp(jabort);
    while ((cp = remglob(argv,0)) != NULL) {
	if (*cp == '\0') {
	    mflag = 0;
	    continue;
	}
	if (mflag && confirm(argv[0], cp)) {
	    command("DELE %s", cp);
	    if (!mflag && fromatty) {
		ointer = interactive;
		interactive = 1;
		if (confirm("Continue with", "mdelete")) {
		    mflag++;
		}
		interactive = ointer;
	    }
	}
    }
    signal(SIGINT, oldintr);
    mflag = 0;
}