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
 int S_IROTH ; 
 int S_IWOTH ; 
 int S_IXOTH ; 
 int /*<<< orphan*/  log_warn (char*) ; 
 int /*<<< orphan*/  log_warnx (char*,char const*) ; 
 int stat (char const*,struct stat*) ; 

__attribute__((used)) static void
check_perms(const char *path)
{
	struct stat sb;
	int error;

	error = stat(path, &sb);
	if (error != 0) {
		log_warn("stat");
		return;
	}
	if (sb.st_mode & S_IWOTH) {
		log_warnx("%s is world-writable", path);
	} else if (sb.st_mode & S_IROTH) {
		log_warnx("%s is world-readable", path);
	} else if (sb.st_mode & S_IXOTH) {
		/*
		 * Ok, this one doesn't matter, but still do it,
		 * just for consistency.
		 */
		log_warnx("%s is world-executable", path);
	}

	/*
	 * XXX: Should we also check for owner != 0?
	 */
}