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
struct dirent {int /*<<< orphan*/  d_name; } ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int error (char*,char const*) ; 
 int /*<<< orphan*/  is_dot_or_dotdot (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * opendir (char const*) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  string_list_insert (struct string_list*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int read_directory_contents(const char *path, struct string_list *list)
{
	DIR *dir;
	struct dirent *e;

	if (!(dir = opendir(path)))
		return error("Could not open directory %s", path);

	while ((e = readdir(dir)))
		if (!is_dot_or_dotdot(e->d_name))
			string_list_insert(list, e->d_name);

	closedir(dir);
	return 0;
}