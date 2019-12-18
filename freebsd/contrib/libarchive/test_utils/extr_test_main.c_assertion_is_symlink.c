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
 int /*<<< orphan*/  failure_start (char const*,int,char*,char const*,...) ; 
 scalar_t__ is_symlink (char const*,int,char const*,char const*,int) ; 

int
assertion_is_symlink(const char *file, int line,
    const char *path, const char *contents, int isdir)
{
	if (is_symlink(file, line, path, contents, isdir))
		return (1);
	if (contents)
		failure_start(file, line, "File %s is not a symlink to %s",
		    path, contents);
	else
		failure_start(file, line, "File %s is not a symlink", path);
	failure_finish(NULL);
	return (0);
}