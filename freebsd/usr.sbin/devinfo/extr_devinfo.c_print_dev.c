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
struct devinfo_dev {char* dd_name; char* dd_pnpinfo; char* dd_location; int dd_flags; } ;

/* Variables and functions */
 int DF_ENABLED ; 
 int DF_SUSPENDED ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ vflag ; 

__attribute__((used)) static void
print_dev(struct devinfo_dev *dev)
{

	printf("%s", dev->dd_name[0] ? dev->dd_name : "unknown");
	if (vflag && *dev->dd_pnpinfo)
		printf(" pnpinfo %s", dev->dd_pnpinfo);
	if (vflag && *dev->dd_location)
		printf(" at %s", dev->dd_location);
	if (!(dev->dd_flags & DF_ENABLED))
		printf(" (disabled)");
	else if (dev->dd_flags & DF_SUSPENDED)
		printf(" (suspended)");
}