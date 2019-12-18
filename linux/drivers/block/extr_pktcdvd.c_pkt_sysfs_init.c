#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  class_groups; int /*<<< orphan*/  class_release; int /*<<< orphan*/  owner; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_NAME ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 TYPE_1__* class_pktcdvd ; 
 int /*<<< orphan*/  class_pktcdvd_groups ; 
 int /*<<< orphan*/  class_pktcdvd_release ; 
 int class_register (TYPE_1__*) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 TYPE_1__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int pkt_sysfs_init(void)
{
	int ret = 0;

	/*
	 * create control files in sysfs
	 * /sys/class/pktcdvd/...
	 */
	class_pktcdvd = kzalloc(sizeof(*class_pktcdvd), GFP_KERNEL);
	if (!class_pktcdvd)
		return -ENOMEM;
	class_pktcdvd->name = DRIVER_NAME;
	class_pktcdvd->owner = THIS_MODULE;
	class_pktcdvd->class_release = class_pktcdvd_release;
	class_pktcdvd->class_groups = class_pktcdvd_groups;
	ret = class_register(class_pktcdvd);
	if (ret) {
		kfree(class_pktcdvd);
		class_pktcdvd = NULL;
		pr_err("failed to create class pktcdvd\n");
		return ret;
	}
	return 0;
}