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
 int /*<<< orphan*/  err (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mib ; 
 scalar_t__ miblen ; 
 scalar_t__ nitems (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pathctl ; 
 scalar_t__ sysctlnametomib (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static void
getmib(void)
{

	/* have we already fetched it? */
	if (miblen != 0)
		return;
	
	miblen = nitems(mib);
	if (sysctlnametomib(pathctl, mib, &miblen) != 0)
		err(1, "sysctlnametomib(%s)", pathctl);
}