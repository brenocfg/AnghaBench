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
struct indent_arg {int indent; struct devinfo_dev* arg; } ;
struct devinfo_dev {scalar_t__* dd_name; scalar_t__ dd_state; } ;

/* Variables and functions */
 scalar_t__ DS_ATTACHED ; 
 int devinfo_foreach_device_child (struct devinfo_dev*,int (*) (struct devinfo_dev*,void*),void*) ; 
 int /*<<< orphan*/  devinfo_foreach_rman (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  print_dev (struct devinfo_dev*) ; 
 int /*<<< orphan*/  print_device_rman_resources ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ rflag ; 
 scalar_t__ vflag ; 

int
print_device(struct devinfo_dev *dev, void *arg)
{
	struct indent_arg	ia;
	int			i, indent;

	if (vflag || (dev->dd_name[0] != 0 && dev->dd_state >= DS_ATTACHED)) {
		indent = (int)(intptr_t)arg;
		for (i = 0; i < indent; i++)
			printf(" ");
		print_dev(dev);
		printf("\n");
		if (rflag) {
			ia.indent = indent + 4;
			ia.arg = dev;
			devinfo_foreach_rman(print_device_rman_resources,
			    (void *)&ia);
		}
	}

	return(devinfo_foreach_device_child(dev, print_device,
	    (void *)((char *)arg + 2)));
}