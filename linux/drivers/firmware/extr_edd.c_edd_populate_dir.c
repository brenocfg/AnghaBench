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
struct edd_device {int /*<<< orphan*/  kobj; } ;
struct edd_attribute {int /*<<< orphan*/  attr; scalar_t__ (* test ) (struct edd_device*) ;} ;

/* Variables and functions */
 struct edd_attribute** edd_attrs ; 
 int /*<<< orphan*/  edd_create_symlink_to_pcidev (struct edd_device*) ; 
 scalar_t__ stub1 (struct edd_device*) ; 
 int sysfs_create_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void edd_populate_dir(struct edd_device * edev)
{
	struct edd_attribute * attr;
	int error = 0;
	int i;

	for (i = 0; (attr = edd_attrs[i]) && !error; i++) {
		if (!attr->test ||
		    (attr->test && attr->test(edev)))
			error = sysfs_create_file(&edev->kobj,&attr->attr);
	}

	if (!error) {
		edd_create_symlink_to_pcidev(edev);
	}
}