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
struct stat {int st_mode; scalar_t__ st_atime; scalar_t__ st_mtime; } ;
struct dirent {scalar_t__ d_ino; char* d_name; } ;
typedef  int /*<<< orphan*/  path ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int MAXPATHLEN ; 
 int MODEMASK ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/ * opendir (char*) ; 
 scalar_t__ pflag ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remout ; 
 scalar_t__ response () ; 
 int /*<<< orphan*/  run_err (char*,char*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 
 int /*<<< orphan*/  source (int,char**) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 
 char* strrchr (char*,char) ; 
 int /*<<< orphan*/  write (int /*<<< orphan*/ ,char*,int) ; 

void
rsource(char *name, struct stat *statp)
{
	DIR *dirp;
	struct dirent *dp;
	char *last, *vect[1], path[MAXPATHLEN];

	if (!(dirp = opendir(name))) {
		run_err("%s: %s", name, strerror(errno));
		return;
	}
	last = strrchr(name, '/');
	if (last == 0)
		last = name;
	else
		last++;
	if (pflag) {
		snprintf(path, sizeof(path), "T%ld 0 %ld 0\n",
		    (long)statp->st_mtime,
		    (long)statp->st_atime);
		write(remout, path, strlen(path));
		if (response() < 0) {
			closedir(dirp);
			return;
		}
	}
	snprintf(path, sizeof(path),
		 "D%04o %d %s\n",
		 (unsigned int)(statp->st_mode & MODEMASK), 0, last);
	write(remout, path, strlen(path));
	if (response() < 0) {
		closedir(dirp);
		return;
	}
	while ((dp = readdir(dirp)) != NULL) {
		if (dp->d_ino == 0)
			continue;
		if (!strcmp(dp->d_name, ".") || !strcmp(dp->d_name, ".."))
			continue;
		if (strlen(name) + 1 + strlen(dp->d_name) >= MAXPATHLEN - 1) {
			run_err("%s/%s: name too long", name, dp->d_name);
			continue;
		}
		snprintf(path, sizeof(path), "%s/%s", name, dp->d_name);
		vect[0] = path;
		source(1, vect);
	}
	closedir(dirp);
	write(remout, "E\n", 2);
	response();
}