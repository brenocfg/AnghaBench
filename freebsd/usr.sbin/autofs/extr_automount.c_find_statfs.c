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
struct statfs {int /*<<< orphan*/  f_mntonname; } ;

/* Variables and functions */
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static const struct statfs *
find_statfs(const struct statfs *mntbuf, int nitems, const char *mountpoint)
{
	int i;

	for (i = 0; i < nitems; i++) {
		if (strcmp(mntbuf[i].f_mntonname, mountpoint) == 0)
			return (mntbuf + i);
	}

	return (NULL);
}