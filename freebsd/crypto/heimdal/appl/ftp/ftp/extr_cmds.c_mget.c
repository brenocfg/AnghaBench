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
 int MaxPathLen ; 
 int /*<<< orphan*/  SIGINT ; 
 scalar_t__ TYPE_I ; 
 int /*<<< orphan*/  another (int*,char***,char*) ; 
 int code ; 
 scalar_t__ confirm (char*,char*) ; 
 scalar_t__ curtype ; 
 char* domap (char*) ; 
 char* dotrans (char*) ; 
 scalar_t__ fromatty ; 
 int interactive ; 
 int /*<<< orphan*/  jabort ; 
 int /*<<< orphan*/  mabort ; 
 scalar_t__ mapflag ; 
 scalar_t__ mcase ; 
 int mflag ; 
 char* mname ; 
 scalar_t__ ntflag ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  proxy ; 
 int /*<<< orphan*/  recvrequest (char*,char*,char*,char*,int,int /*<<< orphan*/ ) ; 
 char* remglob (char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setjmp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ suspicious_filename (char*) ; 
 int /*<<< orphan*/  tolower (int) ; 

void
mget(int argc, char **argv)
{
	sighand oldintr;
	int ch, ointer;
	char *cp, *tp, *tp2, tmpbuf[MaxPathLen];

	if (argc < 2 && !another(&argc, &argv, "remote-files")) {
		printf("usage: %s remote-files\n", argv[0]);
		code = -1;
		return;
	}
	mname = argv[0];
	mflag = 1;
	oldintr = signal(SIGINT, mabort);
	setjmp(jabort);
	while ((cp = remglob(argv,proxy)) != NULL) {
		if (*cp == '\0') {
			mflag = 0;
			continue;
		}
		if (mflag && suspicious_filename(cp))
		    printf("*** Suspicious filename: %s\n", cp);
		if (mflag && confirm(argv[0], cp)) {
			tp = cp;
			if (mcase) {
				for (tp2 = tmpbuf;(ch = (unsigned char)*tp++);)
					*tp2++ = tolower(ch);
				*tp2 = '\0';
				tp = tmpbuf;
			}
			if (ntflag) {
				tp = dotrans(tp);
			}
			if (mapflag) {
				tp = domap(tp);
			}
			recvrequest("RETR", tp, cp,
				    curtype == TYPE_I ? "wb" : "w",
				    tp != cp || !interactive, 0);
			if (!mflag && fromatty) {
				ointer = interactive;
				interactive = 1;
				if (confirm("Continue with","mget")) {
					mflag++;
				}
				interactive = ointer;
			}
		}
	}
	signal(SIGINT,oldintr);
	mflag = 0;
}