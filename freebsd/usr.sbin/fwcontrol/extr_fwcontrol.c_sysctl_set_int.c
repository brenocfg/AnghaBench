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
 int /*<<< orphan*/  err (int,char*,char const*) ; 
 scalar_t__ sysctlbyname (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int) ; 

__attribute__((used)) static void
sysctl_set_int(const char *name, int val)
{
	if (sysctlbyname(name, NULL, NULL, &val, sizeof(int)) < 0)
		err(1, "sysctl %s failed.", name);
}