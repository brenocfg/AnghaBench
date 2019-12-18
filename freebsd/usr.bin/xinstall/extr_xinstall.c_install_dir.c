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
struct stat {int /*<<< orphan*/  st_mode; } ;
typedef  scalar_t__ gid_t ;

/* Variables and functions */
 scalar_t__ EEXIST ; 
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  EX_OSERR ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ chmod (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ chown (char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  dounpriv ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ gid ; 
 int /*<<< orphan*/  metadata_log (char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ mkdir (char*,int) ; 
 int /*<<< orphan*/  mode ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 scalar_t__ stat (char*,struct stat*) ; 
 scalar_t__ uid ; 
 scalar_t__ verbose ; 
 int /*<<< orphan*/  warn (char*,scalar_t__,char*,...) ; 

__attribute__((used)) static void
install_dir(char *path)
{
	char *p;
	struct stat sb;
	int ch, tried_mkdir;

	for (p = path;; ++p)
		if (!*p || (p != path && *p  == '/')) {
			tried_mkdir = 0;
			ch = *p;
			*p = '\0';
again:
			if (stat(path, &sb) < 0) {
				if (errno != ENOENT || tried_mkdir)
					err(EX_OSERR, "stat %s", path);
				if (mkdir(path, 0755) < 0) {
					tried_mkdir = 1;
					if (errno == EEXIST)
						goto again;
					err(EX_OSERR, "mkdir %s", path);
				}
				if (verbose)
					(void)printf("install: mkdir %s\n",
					    path);
			} else if (!S_ISDIR(sb.st_mode))
				errx(EX_OSERR, "%s exists but is not a directory", path);
			if (!(*p = ch))
				break;
 		}

	if (!dounpriv) {
		if ((gid != (gid_t)-1 || uid != (uid_t)-1) &&
		    chown(path, uid, gid))
			warn("chown %u:%u %s", uid, gid, path);
		/* XXXBED: should we do the chmod in the dounpriv case? */
		if (chmod(path, mode))
			warn("chmod %o %s", mode, path);
	}
	metadata_log(path, "dir", NULL, NULL, NULL, 0);
}