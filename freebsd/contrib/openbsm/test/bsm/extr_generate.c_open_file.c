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
 int /*<<< orphan*/  EX_CANTCREAT ; 
 int O_CREAT ; 
 int O_EXCL ; 
 int O_WRONLY ; 
 int PATH_MAX ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*,char const*) ; 
 int open (char*,int,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,char const*) ; 
 int /*<<< orphan*/  unlink (char*) ; 

__attribute__((used)) static int
open_file(const char *directory, const char *name)
{
	char pathname[PATH_MAX];
	int fd;

	snprintf(pathname, PATH_MAX, "%s/%s", directory, name);
	(void)unlink(pathname);
	fd = open(pathname, O_WRONLY | O_CREAT | O_EXCL, 0600);
	if (fd < 0)
		err(EX_CANTCREAT, "open: %s", name);
	return (fd);
}