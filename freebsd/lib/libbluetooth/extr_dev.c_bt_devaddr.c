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
struct bt_devinfo {int /*<<< orphan*/  bdaddr; int /*<<< orphan*/  devname; } ;
typedef  int /*<<< orphan*/  bdaddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  bdaddr_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ bt_devinfo (struct bt_devinfo*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 

int
bt_devaddr(char const *devname, bdaddr_t *addr)
{
	struct bt_devinfo	di;

	strlcpy(di.devname, devname, sizeof(di.devname));

	if (bt_devinfo(&di) < 0)
		return (0);

	if (addr != NULL)
		bdaddr_copy(addr, &di.bdaddr);

	return (1);
}