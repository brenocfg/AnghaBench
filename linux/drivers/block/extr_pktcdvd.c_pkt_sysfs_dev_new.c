#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pktcdvd_device {TYPE_1__* dev; void* kobj_wqueue; void* kobj_stat; int /*<<< orphan*/  name; } ;
struct TYPE_3__ {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (TYPE_1__*) ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ class_pktcdvd ; 
 TYPE_1__* device_create (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kobj_pkt_type_stat ; 
 int /*<<< orphan*/  kobj_pkt_type_wqueue ; 
 void* pkt_kobj_create (struct pktcdvd_device*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pkt_sysfs_dev_new(struct pktcdvd_device *pd)
{
	if (class_pktcdvd) {
		pd->dev = device_create(class_pktcdvd, NULL, MKDEV(0, 0), NULL,
					"%s", pd->name);
		if (IS_ERR(pd->dev))
			pd->dev = NULL;
	}
	if (pd->dev) {
		pd->kobj_stat = pkt_kobj_create(pd, "stat",
					&pd->dev->kobj,
					&kobj_pkt_type_stat);
		pd->kobj_wqueue = pkt_kobj_create(pd, "write_queue",
					&pd->dev->kobj,
					&kobj_pkt_type_wqueue);
	}
}