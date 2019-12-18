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

/* Variables and functions */
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ lstat (char*,struct stat*) ; 

__attribute__((used)) static int
check_dirpath(char *dirp)
{
	char *cp;
	int ret = 1;
	struct stat sb;

	cp = dirp + 1;
	while (*cp && ret) {
		if (*cp == '/') {
			*cp = '\0';
			if (lstat(dirp, &sb) < 0 || !S_ISDIR(sb.st_mode))
				ret = 0;
			*cp = '/';
		}
		cp++;
	}
	if (lstat(dirp, &sb) < 0 || !S_ISDIR(sb.st_mode))
		ret = 0;
	return (ret);
}