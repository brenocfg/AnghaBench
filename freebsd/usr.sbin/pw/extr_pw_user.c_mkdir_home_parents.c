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
struct stat {int /*<<< orphan*/  st_mode; } ;

/* Variables and functions */
 scalar_t__ EEXIST ; 
 int /*<<< orphan*/  EX_DATAERR ; 
 int /*<<< orphan*/  EX_OSFILE ; 
 int /*<<< orphan*/  EX_UNAVAILABLE ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _DEF_DIRMODE ; 
 int /*<<< orphan*/  asprintf (char**,char*,char*) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  fchownat (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int fstatat (int,char const*,struct stat*,int /*<<< orphan*/ ) ; 
 int mkdirat (int,char*,int /*<<< orphan*/ ) ; 
 char* strchr (char*,char) ; 
 char* strdup (char const*) ; 
 char* strrchr (char*,char) ; 
 int /*<<< orphan*/  symlinkat (char*,int,char*) ; 

__attribute__((used)) static void
mkdir_home_parents(int dfd, const char *dir)
{
	struct stat st;
	char *dirs, *tmp;

	if (*dir != '/')
		errx(EX_DATAERR, "invalid base directory for home '%s'", dir);

	dir++;

	if (fstatat(dfd, dir, &st, 0) != -1) {
		if (S_ISDIR(st.st_mode))
			return;
		errx(EX_OSFILE, "root home `/%s' is not a directory", dir);
	}

	dirs = strdup(dir);
	if (dirs == NULL)
		errx(EX_UNAVAILABLE, "out of memory");

	tmp = strrchr(dirs, '/');
	if (tmp == NULL) {
		free(dirs);
		return;
	}
	tmp[0] = '\0';

	/*
	 * This is a kludge especially for Joerg :)
	 * If the home directory would be created in the root partition, then
	 * we really create it under /usr which is likely to have more space.
	 * But we create a symlink from cnf->home -> "/usr" -> cnf->home
	 */
	if (strchr(dirs, '/') == NULL) {
		asprintf(&tmp, "usr/%s", dirs);
		if (tmp == NULL)
			errx(EX_UNAVAILABLE, "out of memory");
		if (mkdirat(dfd, tmp, _DEF_DIRMODE) != -1 || errno == EEXIST) {
			fchownat(dfd, tmp, 0, 0, 0);
			symlinkat(tmp, dfd, dirs);
		}
		free(tmp);
	}
	tmp = dirs;
	if (fstatat(dfd, dirs, &st, 0) == -1) {
		while ((tmp = strchr(tmp + 1, '/')) != NULL) {
			*tmp = '\0';
			if (fstatat(dfd, dirs, &st, 0) == -1) {
				if (mkdirat(dfd, dirs, _DEF_DIRMODE) == -1)
					err(EX_OSFILE,  "'%s' (root home parent) is not a directory", dirs);
			}
			*tmp = '/';
		}
	}
	if (fstatat(dfd, dirs, &st, 0) == -1) {
		if (mkdirat(dfd, dirs, _DEF_DIRMODE) == -1)
			err(EX_OSFILE,  "'%s' (root home parent) is not a directory", dirs);
		fchownat(dfd, dirs, 0, 0, 0);
	}

	free(dirs);
}