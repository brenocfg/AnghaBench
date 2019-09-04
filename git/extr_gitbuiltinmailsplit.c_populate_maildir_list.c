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
struct string_list {int dummy; } ;
struct dirent {char* d_name; } ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  error_errno (char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/ * opendir (char*) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  string_list_insert (struct string_list*,char*) ; 
 char* xstrfmt (char*,char const*,char*) ; 

__attribute__((used)) static int populate_maildir_list(struct string_list *list, const char *path)
{
	DIR *dir;
	struct dirent *dent;
	char *name = NULL;
	char *subs[] = { "cur", "new", NULL };
	char **sub;
	int ret = -1;

	for (sub = subs; *sub; ++sub) {
		free(name);
		name = xstrfmt("%s/%s", path, *sub);
		if ((dir = opendir(name)) == NULL) {
			if (errno == ENOENT)
				continue;
			error_errno("cannot opendir %s", name);
			goto out;
		}

		while ((dent = readdir(dir)) != NULL) {
			if (dent->d_name[0] == '.')
				continue;
			free(name);
			name = xstrfmt("%s/%s", *sub, dent->d_name);
			string_list_insert(list, name);
		}

		closedir(dir);
	}

	ret = 0;

out:
	free(name);
	return ret;
}