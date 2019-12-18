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
struct statfs {char const* f_mntonname; int /*<<< orphan*/  f_fstypename; } ;
struct stat {scalar_t__ st_ino; int /*<<< orphan*/  st_mode; } ;
struct cfjail {int /*<<< orphan*/ * intparams; } ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 size_t KP_PATH ; 
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 char* alloca (int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  jail_warnx (struct cfjail*,char*,char const*,char const*,...) ; 
 scalar_t__ lstat (char*,struct stat*) ; 
 scalar_t__ stat (char const*,struct stat*) ; 
 scalar_t__ statfs (char const*,struct statfs*) ; 
 char* strchr (char*,char) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 char const* strerror (scalar_t__) ; 
 char* string_param (int /*<<< orphan*/ ) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncmp (char const*,char const*,size_t) ; 

__attribute__((used)) static int
check_path(struct cfjail *j, const char *pname, const char *path, int isfile,
    const char *umount_type)
{
	struct stat st, mpst;
	struct statfs stfs;
	char *tpath, *p;
	const char *jailpath;
	size_t jplen;

	if (path[0] != '/') {
		jail_warnx(j, "%s: %s: not an absolute pathname",
		    pname, path);
		return -1;
	}
	/*
	 * Only check for symlinks in components below the jail's path,
	 * since that's where the security risk lies.
	 */
	jailpath = string_param(j->intparams[KP_PATH]);
	if (jailpath == NULL)
		jailpath = "";
	jplen = strlen(jailpath);
	if (!strncmp(path, jailpath, jplen) && path[jplen] == '/') {
		tpath = alloca(strlen(path) + 1);
		strcpy(tpath, path);
		for (p = tpath + jplen; p != NULL; ) {
			p = strchr(p + 1, '/');
			if (p)
				*p = '\0';
			if (lstat(tpath, &st) < 0) {
				if (errno == ENOENT && isfile && !p)
					break;
				jail_warnx(j, "%s: %s: %s", pname, tpath,
				    strerror(errno));
				return -1;
			}
			if (S_ISLNK(st.st_mode)) {
				jail_warnx(j, "%s: %s is a symbolic link",
				    pname, tpath);
				return -1;
			}
			if (p)
				*p = '/';
		}
	}
	if (umount_type != NULL) {
		if (stat(path, &st) < 0 || statfs(path, &stfs) < 0) {
			jail_warnx(j, "%s: %s: %s", pname, path,
			    strerror(errno));
			return -1;
		}
		if (stat(stfs.f_mntonname, &mpst) < 0) {
			jail_warnx(j, "%s: %s: %s", pname, stfs.f_mntonname,
			    strerror(errno));
			return -1;
		}
		if (st.st_ino != mpst.st_ino) {
			jail_warnx(j, "%s: %s: not a mount point",
			    pname, path);
			return -1;
		}
		if (strcmp(stfs.f_fstypename, umount_type)) {
			jail_warnx(j, "%s: %s: not a %s mount",
			    pname, path, umount_type);
			return -1;
		}
	}
	return 0;
}