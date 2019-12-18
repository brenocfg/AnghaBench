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
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * opendir (char const*) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  string_list_append (struct string_list*,char*) ; 

__attribute__((used)) static int read_dir_paths(struct string_list *out, const char *path)
{
	DIR *dh;
	struct dirent *de;

	dh = opendir(path);
	if (!dh)
		return -1;

	while ((de = readdir(dh)))
		if (de->d_name[0] != '.')
			string_list_append(out, de->d_name);

	closedir(dh);
	return 0;
}