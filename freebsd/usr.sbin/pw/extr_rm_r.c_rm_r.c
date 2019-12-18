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
typedef  scalar_t__ uid_t ;
struct stat {scalar_t__ st_uid; int /*<<< orphan*/  st_mode; } ;
struct dirent {char const* d_name; } ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int /*<<< orphan*/  AT_REMOVEDIR ; 
 int /*<<< orphan*/  AT_SYMLINK_NOFOLLOW ; 
 int /*<<< orphan*/  O_DIRECTORY ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fdopendir (int) ; 
 scalar_t__ fstatat (int,char const*,struct stat*,int /*<<< orphan*/ ) ; 
 int openat (int,char const*,int /*<<< orphan*/ ) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  unlinkat (int,char const*,int /*<<< orphan*/ ) ; 

void
rm_r(int rootfd, const char *path, uid_t uid)
{
	int dirfd;
	DIR *d;
	struct dirent  *e;
	struct stat     st;

	if (*path == '/')
		path++;

	dirfd = openat(rootfd, path, O_DIRECTORY);
	if (dirfd == -1) {
		return;
	}

	d = fdopendir(dirfd);
	while ((e = readdir(d)) != NULL) {
		if (strcmp(e->d_name, ".") == 0 || strcmp(e->d_name, "..") == 0)
			continue;

		if (fstatat(dirfd, e->d_name, &st, AT_SYMLINK_NOFOLLOW) != 0)
			continue;
		if (S_ISDIR(st.st_mode))
			rm_r(dirfd, e->d_name, uid);
		else if (S_ISLNK(st.st_mode) || st.st_uid == uid)
			unlinkat(dirfd, e->d_name, 0);
	}
	closedir(d);
	if (fstatat(rootfd, path, &st, AT_SYMLINK_NOFOLLOW) != 0)
		return;
	unlinkat(rootfd, path, S_ISDIR(st.st_mode) ? AT_REMOVEDIR : 0);
}