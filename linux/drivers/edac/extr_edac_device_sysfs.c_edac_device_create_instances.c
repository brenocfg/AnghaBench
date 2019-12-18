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
struct edac_device_ctl_info {int nr_instances; } ;

/* Variables and functions */
 int /*<<< orphan*/  edac_dbg (int /*<<< orphan*/ ,char*) ; 
 int edac_device_create_instance (struct edac_device_ctl_info*,int) ; 
 int /*<<< orphan*/  edac_device_delete_instance (struct edac_device_ctl_info*,int) ; 

__attribute__((used)) static int edac_device_create_instances(struct edac_device_ctl_info *edac_dev)
{
	int i, j;
	int err;

	edac_dbg(0, "\n");

	/* iterate over creation of the instances */
	for (i = 0; i < edac_dev->nr_instances; i++) {
		err = edac_device_create_instance(edac_dev, i);
		if (err) {
			/* unwind previous instances on error */
			for (j = 0; j < i; j++)
				edac_device_delete_instance(edac_dev, j);
			return err;
		}
	}

	return 0;
}