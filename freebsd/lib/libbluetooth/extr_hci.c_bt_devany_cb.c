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
struct bt_devinfo {int /*<<< orphan*/  devname; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCI_DEVNAME_SIZE ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bt_devany_cb(int s, struct bt_devinfo const *di, void *xdevname)
{
	strlcpy((char *) xdevname, di->devname, HCI_DEVNAME_SIZE);
	return (1);
}