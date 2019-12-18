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
typedef  int time_t ;
struct tm {int dummy; } ;
struct stat {int st_mtime; } ;
struct dirent {int /*<<< orphan*/  d_name; } ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int /*<<< orphan*/  AT_SYMLINK_NOFOLLOW ; 
 char* basename (char*) ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int dirfd (int /*<<< orphan*/ *) ; 
 char* dirname (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int fstatat (int,int /*<<< orphan*/ ,struct stat*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * opendir (char*) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 char* strdup (char const*) ; 
 scalar_t__ validate_old_timelog (int,struct dirent*,char*,struct tm*) ; 
 int /*<<< orphan*/  warn (char*,char const*) ; 
 int /*<<< orphan*/  warnx (char*,char*) ; 

__attribute__((used)) static time_t
mtime_old_timelog(const char *file)
{
	struct stat sb;
	struct tm tm;
	int dir_fd;
	time_t t;
	struct dirent *dp;
	DIR *dirp;
	char *logfname, *logfnamebuf, *dir, *dirbuf;

	t = -1;

	if ((dirbuf = strdup(file)) == NULL) {
		warn("strdup() of '%s'", file);
		return (t);
	}
	dir = dirname(dirbuf);
	if ((logfnamebuf = strdup(file)) == NULL) {
		warn("strdup() of '%s'", file);
		free(dirbuf);
		return (t);
	}
	logfname = basename(logfnamebuf);
	if (logfname[0] == '/') {
		warnx("Invalid log filename '%s'", logfname);
		goto out;
	}

	if ((dirp = opendir(dir)) == NULL) {
		warn("Cannot open log directory '%s'", dir);
		goto out;
	}
	dir_fd = dirfd(dirp);
	/* Open the archive dir and find the most recent archive of logfname. */
	while ((dp = readdir(dirp)) != NULL) {
		if (validate_old_timelog(dir_fd, dp, logfname, &tm) == 0)
			continue;

		if (fstatat(dir_fd, dp->d_name, &sb, AT_SYMLINK_NOFOLLOW) == -1) {
			warn("Cannot stat '%s'", file);
			continue;
		}
		if (t < sb.st_mtime)
			t = sb.st_mtime;
	}
	closedir(dirp);

out:
	free(dirbuf);
	free(logfnamebuf);
	return (t);
}