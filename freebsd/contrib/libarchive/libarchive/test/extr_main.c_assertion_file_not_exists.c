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
 int /*<<< orphan*/  F_OK ; 
 scalar_t__ _access (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ access (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertion_count (char const*,int) ; 
 int /*<<< orphan*/  failure_finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  failure_start (char const*,int,char*,char const*) ; 

int
assertion_file_not_exists(const char *filename, int line, const char *f)
{
	assertion_count(filename, line);

#if defined(_WIN32) && !defined(__CYGWIN__)
	if (_access(f, 0))
		return (1);
#else
	if (access(f, F_OK))
		return (1);
#endif
	failure_start(filename, line, "File should not exist: %s", f);
	failure_finish(NULL);
	return (0);
}