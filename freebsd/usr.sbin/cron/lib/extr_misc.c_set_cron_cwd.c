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
struct stat {int st_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRONDIR ; 
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  ERROR_EXIT ; 
 scalar_t__ OK ; 
 int /*<<< orphan*/  SPOOL_DIR ; 
 int S_IFDIR ; 
 scalar_t__ chdir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 scalar_t__ mkdir (int /*<<< orphan*/ ,int) ; 
 scalar_t__ stat (int /*<<< orphan*/ ,struct stat*) ; 
 int /*<<< orphan*/  warn (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warnx (char*,int /*<<< orphan*/ ) ; 

void
set_cron_cwd()
{
	struct stat	sb;

	/* first check for CRONDIR ("/var/cron" or some such)
	 */
	if (stat(CRONDIR, &sb) < OK && errno == ENOENT) {
		warn("%s", CRONDIR);
		if (OK == mkdir(CRONDIR, 0700)) {
			warnx("%s: created", CRONDIR);
			stat(CRONDIR, &sb);
		} else {
			err(ERROR_EXIT, "%s: mkdir", CRONDIR);
		}
	}
	if (!(sb.st_mode & S_IFDIR))
		err(ERROR_EXIT, "'%s' is not a directory, bailing out", CRONDIR);
	if (chdir(CRONDIR) < OK)
		err(ERROR_EXIT, "cannot chdir(%s), bailing out", CRONDIR);

	/* CRONDIR okay (now==CWD), now look at SPOOL_DIR ("tabs" or some such)
	 */
	if (stat(SPOOL_DIR, &sb) < OK && errno == ENOENT) {
		warn("%s", SPOOL_DIR);
		if (OK == mkdir(SPOOL_DIR, 0700)) {
			warnx("%s: created", SPOOL_DIR);
			stat(SPOOL_DIR, &sb);
		} else {
			err(ERROR_EXIT, "%s: mkdir", SPOOL_DIR);
		}
	}
	if (!(sb.st_mode & S_IFDIR))
		err(ERROR_EXIT, "'%s' is not a directory, bailing out", SPOOL_DIR);
}