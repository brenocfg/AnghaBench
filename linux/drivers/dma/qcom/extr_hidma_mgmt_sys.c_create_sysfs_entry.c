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
struct hidma_mgmt_dev {TYPE_1__* pdev; } ;
struct TYPE_4__ {char* name; int mode; } ;
struct device_attribute {TYPE_2__ attr; int /*<<< orphan*/  store; int /*<<< orphan*/  show; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int device_create_file (int /*<<< orphan*/ *,struct device_attribute*) ; 
 struct device_attribute* devm_kmalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 char* devm_kstrdup (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_values ; 
 int /*<<< orphan*/  show_values ; 
 int /*<<< orphan*/  sysfs_attr_init (TYPE_2__*) ; 

__attribute__((used)) static int create_sysfs_entry(struct hidma_mgmt_dev *dev, char *name, int mode)
{
	struct device_attribute *attrs;
	char *name_copy;

	attrs = devm_kmalloc(&dev->pdev->dev,
			     sizeof(struct device_attribute), GFP_KERNEL);
	if (!attrs)
		return -ENOMEM;

	name_copy = devm_kstrdup(&dev->pdev->dev, name, GFP_KERNEL);
	if (!name_copy)
		return -ENOMEM;

	attrs->attr.name = name_copy;
	attrs->attr.mode = mode;
	attrs->show = show_values;
	attrs->store = set_values;
	sysfs_attr_init(&attrs->attr);

	return device_create_file(&dev->pdev->dev, attrs);
}