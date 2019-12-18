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
typedef  int /*<<< orphan*/  wchar_t ;

/* Variables and functions */
 int /*<<< orphan*/  assertion_count (char const*,int) ; 
 int /*<<< orphan*/  failure_finish (void*) ; 
 int /*<<< orphan*/  failure_start (char const*,int,char*,char const*,char const*) ; 
 scalar_t__ wcscmp (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  wcsdump (char const*,int /*<<< orphan*/  const*) ; 

int
assertion_equal_wstring(const char *file, int line,
    const wchar_t *v1, const char *e1,
    const wchar_t *v2, const char *e2,
    void *extra)
{
	assertion_count(file, line);
	if (v1 == v2)
		return (1);
	if (v1 != NULL && v2 != NULL && wcscmp(v1, v2) == 0)
		return (1);
	failure_start(file, line, "%s != %s", e1, e2);
	wcsdump(e1, v1);
	wcsdump(e2, v2);
	failure_finish(extra);
	return (0);
}