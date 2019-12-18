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
typedef  int /*<<< orphan*/  path ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 int PATH_MAX ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  find_kld_path (char*,char*,int) ; 
 int open (char*,unsigned int,int /*<<< orphan*/ ) ; 
 char* xstrdup (char*) ; 

__attribute__((used)) static int
kld_find_and_open_solib (char *solib, unsigned o_flags, char **temp_pathname)
{
	char path[PATH_MAX];
	int fd;

	*temp_pathname = NULL;
	if (!find_kld_path(solib, path, sizeof(path))) {
		errno = ENOENT;
		return (-1);
	}
	fd = open(path, o_flags, 0);
	if (fd >= 0)
		*temp_pathname = xstrdup(path);
	return (fd);
}