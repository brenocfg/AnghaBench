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
typedef  int /*<<< orphan*/  tempname ;
typedef  int /*<<< orphan*/  sig_t ;
typedef  int /*<<< orphan*/  off_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  Fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Fdopen (int,char*) ; 
 int PATHSIZE ; 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIG_IGN ; 
 char* _PATH_CSHELL ; 
 int /*<<< orphan*/ * collf ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  fseeko (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ fsize (int /*<<< orphan*/ *) ; 
 int mkstemp (char*) ; 
 int /*<<< orphan*/  rm (char*) ; 
 scalar_t__ run_command (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 char* tmpdir ; 
 char* value (char*) ; 
 int /*<<< orphan*/  warn (char*,char*) ; 

void
mespipe(FILE *fp, char cmd[])
{
	FILE *nf;
	int fd;
	sig_t sigint = signal(SIGINT, SIG_IGN);
	char *sh, tempname[PATHSIZE];

	(void)snprintf(tempname, sizeof(tempname),
	    "%s/mail.ReXXXXXXXXXX", tmpdir);
	if ((fd = mkstemp(tempname)) == -1 ||
	    (nf = Fdopen(fd, "w+")) == NULL) {
		warn("%s", tempname);
		goto out;
	}
	(void)rm(tempname);
	/*
	 * stdin = current message.
	 * stdout = new message.
	 */
	if ((sh = value("SHELL")) == NULL)
		sh = _PATH_CSHELL;
	if (run_command(sh,
	    0, fileno(fp), fileno(nf), "-c", cmd, NULL) < 0) {
		(void)Fclose(nf);
		goto out;
	}
	if (fsize(nf) == 0) {
		fprintf(stderr, "No bytes from \"%s\" !?\n", cmd);
		(void)Fclose(nf);
		goto out;
	}
	/*
	 * Take new files.
	 */
	(void)fseeko(nf, (off_t)0, SEEK_END);
	collf = nf;
	(void)Fclose(fp);
out:
	(void)signal(SIGINT, sigint);
}