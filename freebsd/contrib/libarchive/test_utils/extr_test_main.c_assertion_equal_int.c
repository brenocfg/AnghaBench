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
 int /*<<< orphan*/  failure_finish (void*) ; 
 int /*<<< orphan*/  failure_start (char const*,int,char*,char const*,char const*) ; 
 int /*<<< orphan*/  logprintf (char*,char const*,long long,long long,long long) ; 

int
assertion_equal_int(const char *file, int line,
    long long v1, const char *e1, long long v2, const char *e2, void *extra)
{
	assertion_count(file, line);
	if (v1 == v2)
		return (1);
	failure_start(file, line, "%s != %s", e1, e2);
	logprintf("      %s=%lld (0x%llx, 0%llo)\n", e1, v1, v1, v1);
	logprintf("      %s=%lld (0x%llx, 0%llo)\n", e2, v2, v2, v2);
	failure_finish(extra);
	return (0);
}