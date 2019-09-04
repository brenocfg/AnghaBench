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
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  mkpath (char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * opendir (char const*) ; 
 int /*<<< orphan*/  prune_tmp_file (int /*<<< orphan*/ ) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 scalar_t__ starts_with (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void remove_temporary_files(const char *path)
{
	DIR *dir;
	struct dirent *de;

	dir = opendir(path);
	if (!dir) {
		fprintf(stderr, "Unable to open directory %s\n", path);
		return;
	}
	while ((de = readdir(dir)) != NULL)
		if (starts_with(de->d_name, "tmp_"))
			prune_tmp_file(mkpath("%s/%s", path, de->d_name));
	closedir(dir);
}