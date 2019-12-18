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
struct exact_info {char* bus; struct devinfo_dev* dev; int /*<<< orphan*/  loc; } ;
struct devinfo_dev {int dd_flags; int /*<<< orphan*/  dd_location; int /*<<< orphan*/  dd_pnpinfo; int /*<<< orphan*/  dd_name; int /*<<< orphan*/  dd_parent; } ;

/* Variables and functions */
 int DF_ENABLED ; 
 int /*<<< orphan*/  asprintf (char**,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int devinfo_foreach_device_child (struct devinfo_dev*,int (*) (struct devinfo_dev*,void*),void*) ; 
 struct devinfo_dev* devinfo_handle_to_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
find_exact_dev(struct devinfo_dev *dev, void *arg)
{
	struct devinfo_dev *parent;
	char *loc;
	struct exact_info *info;

	info = arg;
	do {
		if (info->dev != NULL)
			break;
		if (!(dev->dd_flags & DF_ENABLED))
			break;
		parent = devinfo_handle_to_device(dev->dd_parent);
		if (strcmp(info->bus, parent->dd_name) != 0)
			break;
		asprintf(&loc, "%s %s", parent->dd_pnpinfo,
		    parent->dd_location);
		if (strcmp(loc, info->loc) == 0)
			info->dev = dev;
		free(loc);
	} while (0);

	return (devinfo_foreach_device_child(dev, find_exact_dev, arg));
}