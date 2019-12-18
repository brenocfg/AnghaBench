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
struct dirent {char const* d_name; } ;
typedef  int /*<<< orphan*/  path ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int /*<<< orphan*/  CONFFILE_REPO ; 
 int /*<<< orphan*/  F_OK ; 
 int MAXPATHLEN ; 
 scalar_t__ access (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * opendir (char const*) ; 
 scalar_t__ read_conf_file (char*,int /*<<< orphan*/ ) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,char*,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static int
load_repositories(const char *repodir)
{
	struct dirent *ent;
	DIR *d;
	char *p;
	size_t n;
	char path[MAXPATHLEN];
	int ret;

	ret = 0;

	if ((d = opendir(repodir)) == NULL)
		return (1);

	while ((ent = readdir(d))) {
		/* Trim out 'repos'. */
		if ((n = strlen(ent->d_name)) <= 5)
			continue;
		p = &ent->d_name[n - 5];
		if (strcmp(p, ".conf") == 0) {
			snprintf(path, sizeof(path), "%s%s%s",
			    repodir,
			    repodir[strlen(repodir) - 1] == '/' ? "" : "/",
			    ent->d_name);
			if (access(path, F_OK) == 0 &&
			    read_conf_file(path, CONFFILE_REPO)) {
				ret = 1;
				goto cleanup;
			}
		}
	}

cleanup:
	closedir(d);

	return (ret);
}