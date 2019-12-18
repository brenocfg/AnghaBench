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
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  int /*<<< orphan*/  u_int ;

/* Variables and functions */
 scalar_t__ sysctlbyname (char const*,int /*<<< orphan*/ *,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xo_err (int,char*,char const*) ; 
 int /*<<< orphan*/  xo_errx (int,char*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
netisr_load_sysctl_uint(const char *name, u_int *p)
{
	size_t retlen;

	retlen = sizeof(u_int);
	if (sysctlbyname(name, p, &retlen, NULL, 0) < 0)
		xo_err(-1, "%s", name);
	if (retlen != sizeof(u_int))
		xo_errx(-1, "%s: invalid len %ju", name, (uintmax_t)retlen);
}