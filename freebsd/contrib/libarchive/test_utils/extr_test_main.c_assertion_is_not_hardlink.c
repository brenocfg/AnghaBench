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
 int /*<<< orphan*/  failure_finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  failure_start (char const*,int,char*,char const*,char const*) ; 
 int /*<<< orphan*/  is_hardlink (char const*,int,char const*,char const*) ; 

int
assertion_is_not_hardlink(const char *file, int line,
    const char *path1, const char *path2)
{
	if (!is_hardlink(file, line, path1, path2))
		return (1);
	failure_start(file, line,
	    "Files %s and %s should not be hardlinked", path1, path2);
	failure_finish(NULL);
	return (0);
}