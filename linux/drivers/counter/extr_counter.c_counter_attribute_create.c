#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct list_head {int dummy; } ;
struct TYPE_4__ {int mode; int /*<<< orphan*/  name; } ;
struct device_attribute {scalar_t__ store; TYPE_2__ attr; scalar_t__ show; } ;
struct counter_device_attr {int /*<<< orphan*/  l; int /*<<< orphan*/  component; struct device_attribute dev_attr; } ;
struct counter_attr_parm {TYPE_1__* group; int /*<<< orphan*/  component; scalar_t__ store; scalar_t__ show; int /*<<< orphan*/  name; int /*<<< orphan*/  prefix; } ;
struct TYPE_3__ {int /*<<< orphan*/  num_attr; struct list_head attr_list; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kasprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct counter_device_attr*) ; 
 struct counter_device_attr* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,struct list_head* const) ; 
 int /*<<< orphan*/  sysfs_attr_init (TYPE_2__*) ; 

__attribute__((used)) static int counter_attribute_create(const struct counter_attr_parm *const parm)
{
	struct counter_device_attr *counter_attr;
	struct device_attribute *dev_attr;
	int err;
	struct list_head *const attr_list = &parm->group->attr_list;

	/* Allocate a Counter device attribute */
	counter_attr = kzalloc(sizeof(*counter_attr), GFP_KERNEL);
	if (!counter_attr)
		return -ENOMEM;
	dev_attr = &counter_attr->dev_attr;

	sysfs_attr_init(&dev_attr->attr);

	/* Configure device attribute */
	dev_attr->attr.name = kasprintf(GFP_KERNEL, "%s%s", parm->prefix,
					parm->name);
	if (!dev_attr->attr.name) {
		err = -ENOMEM;
		goto err_free_counter_attr;
	}
	if (parm->show) {
		dev_attr->attr.mode |= 0444;
		dev_attr->show = parm->show;
	}
	if (parm->store) {
		dev_attr->attr.mode |= 0200;
		dev_attr->store = parm->store;
	}

	/* Store associated Counter component with attribute */
	counter_attr->component = parm->component;

	/* Keep track of the attribute for later cleanup */
	list_add(&counter_attr->l, attr_list);
	parm->group->num_attr++;

	return 0;

err_free_counter_attr:
	kfree(counter_attr);
	return err;
}