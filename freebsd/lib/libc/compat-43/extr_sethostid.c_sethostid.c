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
 int CTL_KERN ; 
 int KERN_HOSTID ; 
 int /*<<< orphan*/  sysctl (int*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,long*,int) ; 

void
sethostid(long hostid)
{
	int mib[2];

	mib[0] = CTL_KERN;
	mib[1] = KERN_HOSTID;
	sysctl(mib, 2, NULL, NULL, &hostid, sizeof hostid);
}