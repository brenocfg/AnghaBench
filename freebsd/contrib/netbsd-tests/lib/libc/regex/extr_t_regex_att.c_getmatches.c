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
 int /*<<< orphan*/  ATF_REQUIRE_MSG (int,char*) ; 
 char* strchr (char const*,char) ; 

__attribute__((used)) static size_t
getmatches(const char *s)
{
	size_t i;
	char *q;
	for (i = 0; (q = strchr(s, '(')) != NULL; i++, s = q + 1)
		continue;
	ATF_REQUIRE_MSG(i != 0, "No parentheses found");
	return i;
}