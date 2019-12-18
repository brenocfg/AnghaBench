#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct stat {int /*<<< orphan*/  st_size; } ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_2__ {char* pw_name; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int STDIN_FILENO ; 
 int /*<<< orphan*/  _PATH_SENDMAIL ; 
 int /*<<< orphan*/  _exit (int) ; 
 int /*<<< orphan*/  close (int) ; 
 char* dayname ; 
 int /*<<< orphan*/  doall ; 
 int /*<<< orphan*/  dup2 (int,int) ; 
 int /*<<< orphan*/  execl (int /*<<< orphan*/ ,char*,char*,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ *) ; 
 int fork () ; 
 scalar_t__ fstat (int /*<<< orphan*/ ,struct stat*) ; 
 int /*<<< orphan*/  path ; 
 scalar_t__ pipe (int*) ; 
 TYPE_1__* pw ; 
 int read (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  rewind (int /*<<< orphan*/ *) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  unlink (int /*<<< orphan*/ ) ; 
 scalar_t__ wait (int*) ; 
 int /*<<< orphan*/  warn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write (int,char*,int) ; 

void
closecal(FILE *fp)
{
	struct stat sbuf;
	int nread, pdes[2], status;
	char buf[1024];

	if (!doall)
		return;

	rewind(fp);
	if (fstat(fileno(fp), &sbuf) || !sbuf.st_size)
		goto done;
	if (pipe(pdes) < 0)
		goto done;
	switch (fork()) {
	case -1:			/* error */
		(void)close(pdes[0]);
		(void)close(pdes[1]);
		goto done;
	case 0:
		/* child -- set stdin to pipe output */
		if (pdes[0] != STDIN_FILENO) {
			(void)dup2(pdes[0], STDIN_FILENO);
			(void)close(pdes[0]);
		}
		(void)close(pdes[1]);
		execl(_PATH_SENDMAIL, "sendmail", "-i", "-t", "-F",
		    "\"Reminder Service\"", (char *)NULL);
		warn(_PATH_SENDMAIL);
		_exit(1);
	}
	/* parent -- write to pipe input */
	(void)close(pdes[0]);

	write(pdes[1], "From: \"Reminder Service\" <", 26);
	write(pdes[1], pw->pw_name, strlen(pw->pw_name));
	write(pdes[1], ">\nTo: <", 7);
	write(pdes[1], pw->pw_name, strlen(pw->pw_name));
	write(pdes[1], ">\nSubject: ", 11);
	write(pdes[1], dayname, strlen(dayname));
	write(pdes[1], "'s Calendar\nPrecedence: bulk\n\n", 30);

	while ((nread = read(fileno(fp), buf, sizeof(buf))) > 0)
		(void)write(pdes[1], buf, nread);
	(void)close(pdes[1]);
done:	(void)fclose(fp);
	(void)unlink(path);
	while (wait(&status) >= 0);
}