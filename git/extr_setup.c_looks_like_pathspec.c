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
 int /*<<< orphan*/  no_wildcard (char const*) ; 
 scalar_t__ starts_with (char const*,char*) ; 

__attribute__((used)) static int looks_like_pathspec(const char *arg)
{
	/* anything with a wildcard character */
	if (!no_wildcard(arg))
		return 1;

	/* long-form pathspec magic */
	if (starts_with(arg, ":("))
		return 1;

	return 0;
}