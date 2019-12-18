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
 char* DEFAULTPAGER ; 
 scalar_t__ EMPTYSTRING (char const*) ; 
 size_t FEAT_MLST ; 
 int /*<<< orphan*/  UPRINTF (char*,char*) ; 
 int code ; 
 int /*<<< orphan*/  confirm (char*,char*) ; 
 int /*<<< orphan*/ * features ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* ftp_malloc (size_t) ; 
 char* getoptionvalue (char*) ; 
 char* globulize (char const*) ; 
 int /*<<< orphan*/  recvrequest (char const*,char const*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,size_t) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  ttyout ; 

void
ls(int argc, char *argv[])
{
	const char *cmd;
	char *remdir, *locbuf;
	const char *locfile;
	int pagecmd, mlsdcmd;

	remdir = NULL;
	locbuf = NULL;
	locfile = "-";
	pagecmd = mlsdcmd = 0;
			/*
			 * the only commands that start with `p' are
			 * the `pager' versions.
			 */
	if (argv[0][0] == 'p')
		pagecmd = 1;
	if (strcmp(argv[0] + pagecmd , "mlsd") == 0) {
		if (! features[FEAT_MLST]) {
			fprintf(ttyout,
			   "MLSD is not supported by the remote server.\n");
			return;
		}
		mlsdcmd = 1;
	}
	if (argc == 0)
		goto usage;

	if (mlsdcmd)
		cmd = "MLSD";
	else if (strcmp(argv[0] + pagecmd, "nlist") == 0)
		cmd = "NLST";
	else
		cmd = "LIST";

	if (argc > 1)
		remdir = argv[1];
	if (argc > 2)
		locfile = argv[2];
	if (argc > 3 || ((pagecmd | mlsdcmd) && argc > 2)) {
 usage:
		if (pagecmd || mlsdcmd)
			UPRINTF("usage: %s [remote-path]\n", argv[0]);
		else
			UPRINTF("usage: %s [remote-path [local-file]]\n",
			    argv[0]);
		code = -1;
		goto freels;
	}

	if (pagecmd) {
		const char *p;
		size_t len;

		p = getoptionvalue("pager");
		if (EMPTYSTRING(p))
			p = DEFAULTPAGER;
		len = strlen(p) + 2;
		locbuf = ftp_malloc(len);
		locbuf[0] = '|';
		(void)strlcpy(locbuf + 1, p, len - 1);
		locfile = locbuf;
	} else if ((strcmp(locfile, "-") != 0) && *locfile != '|') {
		if ((locbuf = globulize(locfile)) == NULL ||
		    !confirm("output to local-file:", locbuf)) {
			code = -1;
			goto freels;
		}
		locfile = locbuf;
	}
	recvrequest(cmd, locfile, remdir, "w", 0, 0);
 freels:
	if (locbuf)
		(void)free(locbuf);
}