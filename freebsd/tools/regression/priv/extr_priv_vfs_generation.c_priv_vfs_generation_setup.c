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
struct test {int dummy; } ;
struct stat {scalar_t__ st_gen; } ;

/* Variables and functions */
 int /*<<< orphan*/  GID_WHEEL ; 
 int MAX_TRIES ; 
 int /*<<< orphan*/  UID_ROOT ; 
 int /*<<< orphan*/  fpath ; 
 int fpath_initialized ; 
 int /*<<< orphan*/  setup_file (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ stat (int /*<<< orphan*/ ,struct stat*) ; 
 int /*<<< orphan*/  unlink (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warnx (char*) ; 

int
priv_vfs_generation_setup(int asroot, int injail, struct test *test)
{
	struct stat sb;
	int i;

	/*
	 * The kernel zeros the generation number field when an unprivileged
	 * user stats a file.  In order to distinguish the two cases, we
	 * therefore require a file that we know has a non-zero generation
	 * number.  We try up to MAX_TRIES times and otherwise fail.
	 */
	for (i = 0; i < MAX_TRIES; i++) {
		setup_file("priv_vfs_generation_setup: fpath", fpath,
		    UID_ROOT, GID_WHEEL, 0644);
		if (stat(fpath, &sb) < 0) {
			warn("priv_vfs_generation_setup: fstat(%s)", fpath);
			(void)unlink(fpath);
			return (-1);
		}
		if (sb.st_gen != 0) {
			fpath_initialized = 1;
			return (0);
		}
	}
	warnx("priv_vfs_generation_setup: unable to create gen file");
	return (-1);
}