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
 int /*<<< orphan*/  GIT_SUPER_PREFIX_ENVIRONMENT ; 
 int /*<<< orphan*/  getenv (int /*<<< orphan*/ ) ; 
 char const* super_prefix ; 
 char* xstrdup_or_null (int /*<<< orphan*/ ) ; 

const char *get_super_prefix(void)
{
	static int initialized;
	if (!initialized) {
		super_prefix = xstrdup_or_null(getenv(GIT_SUPER_PREFIX_ENVIRONMENT));
		initialized = 1;
	}
	return super_prefix;
}