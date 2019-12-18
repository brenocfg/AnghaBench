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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 char* CRON_TAB (int /*<<< orphan*/ ) ; 
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  ERROR_EXIT ; 
 int MAX_FNAME ; 
 int /*<<< orphan*/  Pid ; 
 int /*<<< orphan*/  RealUser ; 
 int /*<<< orphan*/  User ; 
 int /*<<< orphan*/  copy_file (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  log_it (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void
list_cmd() {
	char	n[MAX_FNAME];
	FILE	*f;

	log_it(RealUser, Pid, "LIST", User);
	(void) snprintf(n, sizeof(n), CRON_TAB(User));
	if (!(f = fopen(n, "r"))) {
		if (errno == ENOENT)
			errx(ERROR_EXIT, "no crontab for %s", User);
		else
			err(ERROR_EXIT, "%s", n);
	}

	/* file is open. copy to stdout, close.
	 */
	copy_file(f, stdout);
	fclose(f);
}