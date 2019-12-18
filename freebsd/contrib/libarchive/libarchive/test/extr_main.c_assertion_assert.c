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
 int /*<<< orphan*/  failure_start (char const*,int,char*,char const*) ; 

int
assertion_assert(const char *file, int line, int value,
    const char *condition, void *extra)
{
	assertion_count(file, line);
	if (!value) {
		failure_start(file, line, "Assertion failed: %s", condition);
		failure_finish(extra);
	}
	return (value);
}