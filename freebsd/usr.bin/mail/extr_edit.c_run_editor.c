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
typedef  scalar_t__ time_t ;
typedef  int /*<<< orphan*/  tempname ;
struct stat {scalar_t__ st_mtime; } ;
typedef  scalar_t__ off_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EOF ; 
 scalar_t__ Fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Fdopen (int,char*) ; 
 int /*<<< orphan*/ * Fopen (char*,char*) ; 
 int PATHSIZE ; 
 char* _PATH_EX ; 
 char* _PATH_VI ; 
 int fchmod (int,int) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ *) ; 
 scalar_t__ fstat (int /*<<< orphan*/ ,struct stat*) ; 
 int getc (int /*<<< orphan*/ *) ; 
 int mkstemp (char*) ; 
 int /*<<< orphan*/  putc (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rm (char*) ; 
 scalar_t__ run_command (char*,int /*<<< orphan*/ ,int,int,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 scalar_t__ stat (char*,struct stat*) ; 
 char* tmpdir ; 
 char* value (char*) ; 
 int /*<<< orphan*/  warn (char*,char*) ; 
 int /*<<< orphan*/  warnx (char*,char*) ; 

FILE *
run_editor(FILE *fp, off_t size, int type, int readonly)
{
	FILE *nf = NULL;
	int t;
	time_t modtime;
	char *edit, tempname[PATHSIZE];
	struct stat statb;

	(void)snprintf(tempname, sizeof(tempname),
	    "%s/mail.ReXXXXXXXXXX", tmpdir);
	if ((t = mkstemp(tempname)) == -1 ||
	    (nf = Fdopen(t, "w")) == NULL) {
		warn("%s", tempname);
		goto out;
	}
	if (readonly && fchmod(t, 0400) == -1) {
		warn("%s", tempname);
		(void)rm(tempname);
		goto out;
	}
	if (size >= 0)
		while (--size >= 0 && (t = getc(fp)) != EOF)
			(void)putc(t, nf);
	else
		while ((t = getc(fp)) != EOF)
			(void)putc(t, nf);
	(void)fflush(nf);
	if (fstat(fileno(nf), &statb) < 0)
		modtime = 0;
	else
		modtime = statb.st_mtime;
	if (ferror(nf)) {
		(void)Fclose(nf);
		warnx("%s", tempname);
		(void)rm(tempname);
		nf = NULL;
		goto out;
	}
	if (Fclose(nf) < 0) {
		warn("%s", tempname);
		(void)rm(tempname);
		nf = NULL;
		goto out;
	}
	nf = NULL;
	if ((edit = value(type == 'e' ? "EDITOR" : "VISUAL")) == NULL)
		edit = type == 'e' ? _PATH_EX : _PATH_VI;
	if (run_command(edit, 0, -1, -1, tempname, NULL) < 0) {
		(void)rm(tempname);
		goto out;
	}
	/*
	 * If in read only mode or file unchanged, just remove the editor
	 * temporary and return.
	 */
	if (readonly) {
		(void)rm(tempname);
		goto out;
	}
	if (stat(tempname, &statb) < 0) {
		warn("%s", tempname);
		goto out;
	}
	if (modtime == statb.st_mtime) {
		(void)rm(tempname);
		goto out;
	}
	/*
	 * Now switch to new file.
	 */
	if ((nf = Fopen(tempname, "a+")) == NULL) {
		warn("%s", tempname);
		(void)rm(tempname);
		goto out;
	}
	(void)rm(tempname);
out:
	return (nf);
}