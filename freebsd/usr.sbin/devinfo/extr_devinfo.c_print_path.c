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
struct devinfo_dev {int /*<<< orphan*/  dd_name; } ;

/* Variables and functions */
 int devinfo_foreach_device_child (struct devinfo_dev*,int (*) (struct devinfo_dev*,void*),void*) ; 
 int /*<<< orphan*/  print_dev (struct devinfo_dev*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ vflag ; 

__attribute__((used)) static int
print_path(struct devinfo_dev *dev, void *xname)
{
	const char *name = xname;
	int rv;

	if (strcmp(dev->dd_name, name) == 0) {
		print_dev(dev);
		if (vflag)
			printf("\n");
		return (1);
	}

	rv = devinfo_foreach_device_child(dev, print_path, xname);
	if (rv == 1) {
		printf(" ");
		print_dev(dev);
		if (vflag)
			printf("\n");
	}
	return (rv);
}