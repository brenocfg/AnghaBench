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
struct ow_devinfo {int /*<<< orphan*/  romid; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct ow_devinfo* device_get_ivars (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int
ow_child_pnpinfo_str(device_t dev, device_t child, char *buf,
    size_t buflen)
{
	struct ow_devinfo *di;

	di = device_get_ivars(child);
	snprintf(buf, buflen, "romid=%8D", &di->romid, ":");
	return (0);
}