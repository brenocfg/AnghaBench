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
 int /*<<< orphan*/  assertion_count (char const*,int) ; 
 scalar_t__ chdir (char const*) ; 
 int /*<<< orphan*/  failure_finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  failure_start (char const*,int,char*,char const*) ; 

int
assertion_chdir(const char *file, int line, const char *pathname)
{
	assertion_count(file, line);
	if (chdir(pathname) == 0)
		return (1);
	failure_start(file, line, "chdir(\"%s\")", pathname);
	failure_finish(NULL);
	return (0);

}