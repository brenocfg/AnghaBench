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
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*,char const*) ; 
 int fchdir (int) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dofchdir(const char *path, const char *errmsg)
{
	int fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		err(EXIT_FAILURE, "open %s", errmsg);
	if (fchdir(fd) == -1)
		err(EXIT_FAILURE, "fchdir %s", errmsg);
	close(fd);
}