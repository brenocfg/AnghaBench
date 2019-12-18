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
typedef  int /*<<< orphan*/  mibname ;
typedef  int /*<<< orphan*/  dummy ;

/* Variables and functions */
 int mfi_unit ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 scalar_t__ sysctlbyname (char*,int*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
mfi_reconfig_supported(void)
{
	char mibname[64];
	size_t len;
	int dummy;

	len = sizeof(dummy);
	snprintf(mibname, sizeof(mibname), "dev.mfi.%d.delete_busy_volumes",
	    mfi_unit);
	return (sysctlbyname(mibname, &dummy, &len, NULL, 0) == 0);
}