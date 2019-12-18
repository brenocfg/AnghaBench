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
typedef  int /*<<< orphan*/  cline ;

/* Variables and functions */
 int BUFSIZ ; 
 int confirmrest ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,...) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ get_line (int /*<<< orphan*/ ,char*,int,char const**) ; 
 scalar_t__ interactive ; 
 scalar_t__ mflag ; 
 int /*<<< orphan*/  stdin ; 
 int tolower (unsigned char) ; 
 int /*<<< orphan*/  ttyout ; 

__attribute__((used)) static int
confirm(const char *cmd, const char *file)
{
	const char *errormsg;
	char cline[BUFSIZ];
	const char *promptleft, *promptright;

	if (!interactive || confirmrest)
		return (1);
	if (file == NULL) {
		promptleft = "Continue with";
		promptright = cmd;
	} else {
		promptleft = cmd;
		promptright = file;
	}
	while (1) {
		fprintf(ttyout, "%s %s [anpqy?]? ", promptleft, promptright);
		(void)fflush(ttyout);
		if (get_line(stdin, cline, sizeof(cline), &errormsg) < 0) {
			mflag = 0;
			fprintf(ttyout, "%s; %s aborted\n", errormsg, cmd);
			return (0);
		}
		switch (tolower((unsigned char)*cline)) {
			case 'a':
				confirmrest = 1;
				fprintf(ttyout,
				    "Prompting off for duration of %s.\n", cmd);
				break;
			case 'p':
				interactive = 0;
				fputs("Interactive mode: off.\n", ttyout);
				break;
			case 'q':
				mflag = 0;
				fprintf(ttyout, "%s aborted.\n", cmd);
				/* FALLTHROUGH */
			case 'n':
				return (0);
			case '?':
				fprintf(ttyout,
				    "  confirmation options:\n"
				    "\ta  answer `yes' for the duration of %s\n"
				    "\tn  answer `no' for this file\n"
				    "\tp  turn off `prompt' mode\n"
				    "\tq  stop the current %s\n"
				    "\ty  answer `yes' for this file\n"
				    "\t?  this help list\n",
				    cmd, cmd);
				continue;	/* back to while(1) */
		}
		return (1);
	}
	/* NOTREACHED */
}