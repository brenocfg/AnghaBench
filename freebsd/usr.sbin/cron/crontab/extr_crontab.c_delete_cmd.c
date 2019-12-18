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
typedef  int /*<<< orphan*/  n ;

/* Variables and functions */
 char* CRON_TAB (char*) ; 
 scalar_t__ ENOENT ; 
 int EOF ; 
 int /*<<< orphan*/  ERROR_EXIT ; 
 int MAX_FNAME ; 
 int /*<<< orphan*/  Pid ; 
 int /*<<< orphan*/  RealUser ; 
 int /*<<< orphan*/  STDIN_FILENO ; 
 char* User ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  fflag ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int getchar () ; 
 scalar_t__ isatty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_it (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  poke_daemon () ; 
 int /*<<< orphan*/  snprintf (char*,int,char*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ unlink (char*) ; 

__attribute__((used)) static void
delete_cmd() {
	char	n[MAX_FNAME];
	int ch, first;

	if (!fflag && isatty(STDIN_FILENO)) {
		(void)fprintf(stderr, "remove crontab for %s? ", User);
		first = ch = getchar();
		while (ch != '\n' && ch != EOF)
			ch = getchar();
		if (first != 'y' && first != 'Y')
			return;
	}

	log_it(RealUser, Pid, "DELETE", User);
	(void) snprintf(n, sizeof(n), CRON_TAB(User));
	if (unlink(n)) {
		if (errno == ENOENT)
			errx(ERROR_EXIT, "no crontab for %s", User);
		else
			err(ERROR_EXIT, "%s", n);
	}
	poke_daemon();
}