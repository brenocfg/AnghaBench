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
 scalar_t__ ENOMEM ; 
 scalar_t__ errno ; 
 int sysctlbyname (char const*,void*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xo_err (int,char*,char const*) ; 

__attribute__((used)) static int
mysysctl(const char *name, void *oldp, size_t *oldlenp)
{
	int error;

	error = sysctlbyname(name, oldp, oldlenp, NULL, 0);
	if (error != 0 && errno != ENOMEM)
		xo_err(1, "sysctl(%s)", name);
	return (error);
}