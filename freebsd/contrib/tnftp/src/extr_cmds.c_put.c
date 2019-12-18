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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int MAXPATHLEN ; 
 int /*<<< orphan*/  UPRINTF (char*,char*) ; 
 int /*<<< orphan*/  another (int*,char***,char*) ; 
 int code ; 
 char* doprocess (char*,int,char const*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* globulize (char*) ; 
 scalar_t__ mapflag ; 
 scalar_t__ ntflag ; 
 int /*<<< orphan*/  sendrequest (char const*,char*,char const*,int) ; 
 scalar_t__ sunique ; 

void
put(int argc, char *argv[])
{
	char buf[MAXPATHLEN];
	const char *cmd;
	int loc = 0;
	char *locfile;
	const char *remfile;

	if (argc == 2) {
		argc++;
		argv[2] = argv[1];
		loc++;
	}
	if (argc == 0 || (argc == 1 && !another(&argc, &argv, "local-file")))
		goto usage;
	if ((argc < 3 && !another(&argc, &argv, "remote-file")) || argc > 3) {
 usage:
		UPRINTF("usage: %s local-file [remote-file]\n", argv[0]);
		code = -1;
		return;
	}
	if ((locfile = globulize(argv[1])) == NULL) {
		code = -1;
		return;
	}
	remfile = argv[2];
	if (loc)	/* If argv[2] is a copy of the old argv[1], update it */
		remfile = locfile;
	cmd = (argv[0][0] == 'a') ? "APPE" : ((sunique) ? "STOU" : "STOR");
	remfile = doprocess(buf, sizeof(buf), remfile,
		0, loc && ntflag, loc && mapflag);
	sendrequest(cmd, locfile, remfile,
	    locfile != argv[1] || remfile != argv[2]);
	free(locfile);
}