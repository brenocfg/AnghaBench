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
 scalar_t__ strcmp (char const*,char const*) ; 
 int /*<<< orphan*/  strdump (char const*,char const*,int,int) ; 
 scalar_t__ strlen (char const*) ; 

int
assertion_equal_string(const char *file, int line,
    const char *v1, const char *e1,
    const char *v2, const char *e2,
    void *extra, int utf8)
{
	int l1, l2;

	assertion_count(file, line);
	if (v1 == v2 || (v1 != NULL && v2 != NULL && strcmp(v1, v2) == 0))
		return (1);
	failure_start(file, line, "%s != %s", e1, e2);
	l1 = (int)strlen(e1);
	l2 = (int)strlen(e2);
	if (l1 < l2)
		l1 = l2;
	strdump(e1, v1, l1, utf8);
	strdump(e2, v2, l1, utf8);
	failure_finish(extra);
	return (0);
}