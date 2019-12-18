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
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  EX_NOINPUT ; 
 int /*<<< orphan*/  EX_OSERR ; 
 int /*<<< orphan*/  _PATH_DEV ; 
 scalar_t__ asprintf (char**,char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*,char const*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int open (char const*,int) ; 

__attribute__((used)) static int
opendev(const char *path, int flags)
{
	int fd;
	char *tstr;

	if ((fd = open(path, flags)) < 0) {
		if (errno == ENOENT && path[0] != '/') {
			if (asprintf(&tstr, "%s%s", _PATH_DEV, path) < 0)
				errx(EX_OSERR, "no memory");
			fd = open(tstr, flags);
			free(tstr);
		}
	}

	if (fd < 0)
		err(EX_NOINPUT, "open failed: %s", path);

	return (fd);
}