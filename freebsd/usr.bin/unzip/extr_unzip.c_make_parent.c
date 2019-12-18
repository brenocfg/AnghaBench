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
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ lstat (char*,struct stat*) ; 
 int /*<<< orphan*/  make_dir (char*,int) ; 
 int /*<<< orphan*/  mkdir (char*,int) ; 
 char* strchr (char*,char) ; 
 char* strrchr (char*,char) ; 
 int /*<<< orphan*/  unlink (char*) ; 

__attribute__((used)) static void
make_parent(char *path)
{
	struct stat sb;
	char *sep;

	sep = strrchr(path, '/');
	if (sep == NULL || sep == path)
		return;
	*sep = '\0';
	if (lstat(path, &sb) == 0) {
		if (S_ISDIR(sb.st_mode)) {
			*sep = '/';
			return;
		}
		unlink(path);
	}
	make_parent(path);
	mkdir(path, 0755);
	*sep = '/';

#if 0
	for (sep = path; (sep = strchr(sep, '/')) != NULL; sep++) {
		/* root in case of absolute d_arg */
		if (sep == path)
			continue;
		*sep = '\0';
		make_dir(path, 0755);
		*sep = '/';
	}
#endif
}