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
typedef  int /*<<< orphan*/  wrkdir ;
typedef  int /*<<< orphan*/  tmpstr ;
typedef  scalar_t__ pid_t ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;
typedef  int /*<<< orphan*/  ACPI_TABLE_HEADER ;

/* Variables and functions */
 int O_CREAT ; 
 int O_WRONLY ; 
 int PATH_MAX ; 
 int STDERR_FILENO ; 
 int STDOUT_FILENO ; 
 int S_IRUSR ; 
 int S_IWUSR ; 
 char* _PATH_TMP ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  execl (char*,char*,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 scalar_t__ fork () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 size_t fread (char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fwrite (char*,int,size_t,int /*<<< orphan*/ ) ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/ * mkdtemp (char*) ; 
 int open (char*,int,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/ * realpath (char const*,char*) ; 
 scalar_t__ rmdir (char*) ; 
 scalar_t__ snprintf (char*,int,char*,char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 int strlen (char const*) ; 
 scalar_t__ unlink (char*) ; 
 scalar_t__ vflag ; 
 int /*<<< orphan*/  wait (int*) ; 
 int /*<<< orphan*/  write_dsdt (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
aml_disassemble(ACPI_TABLE_HEADER *rsdt, ACPI_TABLE_HEADER *dsdp)
{
	char buf[PATH_MAX], tmpstr[PATH_MAX], wrkdir[PATH_MAX];
	const char *iname = "/acpdump.din";
	const char *oname = "/acpdump.dsl";
	const char *tmpdir;
	FILE *fp;
	size_t len;
	int fd, status;
	pid_t pid;

	tmpdir = getenv("TMPDIR");
	if (tmpdir == NULL)
		tmpdir = _PATH_TMP;
	if (realpath(tmpdir, buf) == NULL) {
		perror("realpath tmp dir");
		return;
	}
	len = sizeof(wrkdir) - strlen(iname);
	if ((size_t)snprintf(wrkdir, len, "%s/acpidump.XXXXXX", buf) > len-1 ) {
		fprintf(stderr, "$TMPDIR too long\n");
		return;
	}
	if  (mkdtemp(wrkdir) == NULL) {
		perror("mkdtemp tmp working dir");
		return;
	}
	len = (size_t)snprintf(tmpstr, sizeof(tmpstr), "%s%s", wrkdir, iname);
	assert(len <= sizeof(tmpstr) - 1);
	fd = open(tmpstr, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);
	if (fd < 0) {
		perror("iasl tmp file");
		return;
	}
	write_dsdt(fd, rsdt, dsdp);
	close(fd);

	/* Run iasl -d on the temp file */
	if ((pid = fork()) == 0) {
		close(STDOUT_FILENO);
		if (vflag == 0)
			close(STDERR_FILENO);
		execl("/usr/sbin/iasl", "iasl", "-d", tmpstr, NULL);
		err(1, "exec");
	}
	if (pid > 0)
		wait(&status);
	if (unlink(tmpstr) < 0) {
		perror("unlink");
		goto out;
	}
	if (pid < 0) {
		perror("fork");
		goto out;
	}
	if (status != 0) {
		fprintf(stderr, "iast exit status = %d\n", status);
	}

	/* Dump iasl's output to stdout */
	len = (size_t)snprintf(tmpstr, sizeof(tmpstr), "%s%s", wrkdir, oname);
	assert(len <= sizeof(tmpstr) - 1);
	fp = fopen(tmpstr, "r");
	if (unlink(tmpstr) < 0) {
		perror("unlink");
		goto out;
	}
	if (fp == NULL) {
		perror("iasl tmp file (read)");
		goto out;
	}
	while ((len = fread(buf, 1, sizeof(buf), fp)) > 0)
		fwrite(buf, 1, len, stdout);
	fclose(fp);

    out:
	if (rmdir(wrkdir) < 0)
		perror("rmdir");
}