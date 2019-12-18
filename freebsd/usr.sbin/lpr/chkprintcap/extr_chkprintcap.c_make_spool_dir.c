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
struct stat {int dummy; } ;
struct printer {char* spool_dir; scalar_t__ daemon_user; int /*<<< orphan*/  printer; } ;
struct group {scalar_t__ gr_gid; } ;

/* Variables and functions */
 scalar_t__ SPOOL_DIR_MODE ; 
 int S_IRUSR ; 
 int S_IXUSR ; 
 scalar_t__ chmod (char*,scalar_t__) ; 
 scalar_t__ chown (char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*) ; 
 struct group* getgrnam (char*) ; 
 scalar_t__ mkdir (char*,int) ; 
 int /*<<< orphan*/  note_spool_dir (struct printer const*,struct stat*) ; 
 int /*<<< orphan*/  problems ; 
 scalar_t__ stat (char*,struct stat*) ; 
 int /*<<< orphan*/  warn (char*,char*,...) ; 

__attribute__((used)) static void
make_spool_dir(const struct printer *pp)
{
	char *sd = pp->spool_dir;
	struct group *gr;
	struct stat stab;

	if (mkdir(sd, S_IRUSR | S_IXUSR) < 0) {
		problems++;
		warn("%s: mkdir %s", pp->printer, sd);
		return;
	}
	gr = getgrnam("daemon");
	if (gr == NULL)
		errx(++problems, "cannot locate daemon group");

	if (chown(sd, pp->daemon_user, gr->gr_gid) < 0) {
		++problems;
		warn("%s: cannot change ownership to %ld:%ld", sd,
		     (long)pp->daemon_user, (long)gr->gr_gid);
		return;
	}

	if (chmod(sd, SPOOL_DIR_MODE) < 0) {
		++problems;
		warn("%s: cannot change mode to %lo", sd, (long)SPOOL_DIR_MODE);
		return;
	}
	if (stat(sd, &stab) < 0)
		err(++problems, "stat: %s", sd);

	note_spool_dir(pp, &stab);
}