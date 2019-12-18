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
struct dirent {int /*<<< orphan*/  d_name; } ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int error_errno (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_git_dir () ; 
 char* git_path (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * opendir (int /*<<< orphan*/ ) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 scalar_t__ should_delete_shared_index (char const*) ; 
 int /*<<< orphan*/  skip_prefix (int /*<<< orphan*/ ,char*,char const**) ; 
 int /*<<< orphan*/  strcmp (char const*,char const*) ; 
 scalar_t__ unlink (char const*) ; 
 int /*<<< orphan*/  warning_errno (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int clean_shared_index_files(const char *current_hex)
{
	struct dirent *de;
	DIR *dir = opendir(get_git_dir());

	if (!dir)
		return error_errno(_("unable to open git dir: %s"), get_git_dir());

	while ((de = readdir(dir)) != NULL) {
		const char *sha1_hex;
		const char *shared_index_path;
		if (!skip_prefix(de->d_name, "sharedindex.", &sha1_hex))
			continue;
		if (!strcmp(sha1_hex, current_hex))
			continue;
		shared_index_path = git_path("%s", de->d_name);
		if (should_delete_shared_index(shared_index_path) > 0 &&
		    unlink(shared_index_path))
			warning_errno(_("unable to unlink: %s"), shared_index_path);
	}
	closedir(dir);

	return 0;
}