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
 int sysctlbyname (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,size_t) ; 

__attribute__((used)) static bool
paxset(int global, int enabled)
{
	size_t len = sizeof(int);
	int rv;

	rv = sysctlbyname("security.pax.mprotect.global",
	    NULL, NULL, &global, len);

	if (rv != 0)
		return false;

	rv = sysctlbyname("security.pax.mprotect.enabled",
	    NULL, NULL, &enabled, len);

	if (rv != 0)
		return false;

	return true;
}