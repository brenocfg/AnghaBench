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
typedef  int /*<<< orphan*/  newval ;

/* Variables and functions */
 int /*<<< orphan*/  atf_tc_fail (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  curtain_name ; 
 scalar_t__ sysctlbyname (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static void
set_curtain(int newval)
{

	if (sysctlbyname(curtain_name, NULL, 0, &newval, sizeof(newval)) != 0)
		atf_tc_fail("failed to set %s to %d", curtain_name, newval);
}