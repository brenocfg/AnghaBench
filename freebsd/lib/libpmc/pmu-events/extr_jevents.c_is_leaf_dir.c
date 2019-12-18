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
struct dirent {char* d_name; scalar_t__ d_type; } ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 scalar_t__ DT_DIR ; 
 scalar_t__ DT_UNKNOWN ; 
 int PATH_MAX ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * opendir (char const*) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*,char*) ; 
 scalar_t__ stat (char*,struct stat*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static int is_leaf_dir(const char *fpath)
{
	DIR *d;
	struct dirent *dir;
	int res = 1;

	d = opendir(fpath);
	if (!d)
		return 0;

	while ((dir = readdir(d)) != NULL) {
		if (!strcmp(dir->d_name, ".") || !strcmp(dir->d_name, ".."))
			continue;

		if (dir->d_type == DT_DIR) {
			res = 0;
			break;
		} else if (dir->d_type == DT_UNKNOWN) {
			char path[PATH_MAX];
			struct stat st;

			sprintf(path, "%s/%s", fpath, dir->d_name);
			if (stat(path, &st))
				break;

			if (S_ISDIR(st.st_mode)) {
				res = 0;
				break;
			}
		}
	}

	closedir(d);

	return res;
}