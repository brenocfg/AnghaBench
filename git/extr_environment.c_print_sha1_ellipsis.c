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
 char* getenv (char*) ; 
 int /*<<< orphan*/  strcasecmp (char const*,char*) ; 

int print_sha1_ellipsis(void)
{
	/*
	 * Determine if the calling environment contains the variable
	 * GIT_PRINT_SHA1_ELLIPSIS set to "yes".
	 */
	static int cached_result = -1; /* unknown */

	if (cached_result < 0) {
		const char *v = getenv("GIT_PRINT_SHA1_ELLIPSIS");
		cached_result = (v && !strcasecmp(v, "yes"));
	}
	return cached_result;
}