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
 int /*<<< orphan*/  is_dot_or_dotdot (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * opendir (char const*) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 

int is_empty_dir(const char *path)
{
	DIR *dir = opendir(path);
	struct dirent *e;
	int ret = 1;

	if (!dir)
		return 0;

	while ((e = readdir(dir)) != NULL)
		if (!is_dot_or_dotdot(e->d_name)) {
			ret = 0;
			break;
		}

	closedir(dir);
	return ret;
}