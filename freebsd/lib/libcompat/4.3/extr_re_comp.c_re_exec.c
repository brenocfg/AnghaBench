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
 int /*<<< orphan*/  re_gotexp ; 
 int /*<<< orphan*/  re_regexp ; 
 int regexec (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
re_exec(const char *s)
{
	int rc;

	if (!re_gotexp)
		return (-1);
	rc = regexec(&re_regexp, s, 0, NULL, 0);
	return (rc == 0 ? 1 : 0);
}