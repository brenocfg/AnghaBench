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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  time_t ;
typedef  int /*<<< orphan*/  line ;
typedef  int /*<<< orphan*/  host ;

/* Variables and functions */
 int MAXHOSTNAMELEN ; 
 int /*<<< orphan*/  O_WRONLY ; 
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  _PATH_DEV ; 
 char* ctime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  done ; 
 int /*<<< orphan*/  err (int,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fdopen (int,char*) ; 
 int /*<<< orphan*/ * fgetws (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ gethostname (char*,int) ; 
 int openat (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char const*,char*,char*,char*) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/ * stdout ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wr_fputs (int /*<<< orphan*/ *) ; 

void
do_write(int devfd, char *tty, char *mytty, const char *login)
{
	char *nows;
	time_t now;
	char host[MAXHOSTNAMELEN];
	wchar_t line[512];
	int fd;

	fd = openat(devfd, tty, O_WRONLY);
	if (fd < 0)
		err(1, "openat(%s%s)", _PATH_DEV, tty);
	fclose(stdout);
	stdout = fdopen(fd, "w");
	if (stdout == NULL)
		err(1, "%s%s", _PATH_DEV, tty);

	(void)signal(SIGINT, done);
	(void)signal(SIGHUP, done);

	/* print greeting */
	if (gethostname(host, sizeof(host)) < 0)
		(void)strcpy(host, "???");
	now = time((time_t *)NULL);
	nows = ctime(&now);
	nows[16] = '\0';
	(void)printf("\r\n\007\007\007Message from %s@%s on %s at %s ...\r\n",
	    login, host, mytty, nows + 11);

	while (fgetws(line, sizeof(line)/sizeof(wchar_t), stdin) != NULL)
		wr_fputs(line);
}