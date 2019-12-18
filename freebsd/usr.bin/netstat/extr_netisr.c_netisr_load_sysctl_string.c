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
 scalar_t__ sysctlbyname (char const*,char*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xo_err (int,char*,char const*) ; 

__attribute__((used)) static void
netisr_load_sysctl_string(const char *name, char *p, size_t len)
{
	size_t retlen;

	retlen = len;
	if (sysctlbyname(name, p, &retlen, NULL, 0) < 0)
		xo_err(-1, "%s", name);
	p[len - 1] = '\0';
}