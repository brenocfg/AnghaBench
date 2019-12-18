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

/* Variables and functions */
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  is_missing_file_error (int /*<<< orphan*/ ) ; 
 scalar_t__ rmdir (char*) ; 
 char* strrchr (char const*,char) ; 
 scalar_t__ unlink (char const*) ; 
 char* xstrdup (char const*) ; 

int remove_path(const char *name)
{
	char *slash;

	if (unlink(name) && !is_missing_file_error(errno))
		return -1;

	slash = strrchr(name, '/');
	if (slash) {
		char *dirs = xstrdup(name);
		slash = dirs + (slash - name);
		do {
			*slash = '\0';
		} while (rmdir(dirs) == 0 && (slash = strrchr(dirs, '/')));
		free(dirs);
	}
	return 0;
}