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
struct ipmi_reg_list {int /*<<< orphan*/  link; int /*<<< orphan*/  dev; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_create (int /*<<< orphan*/ ,struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  ipmi_class ; 
 int /*<<< orphan*/  ipmi_major ; 
 struct ipmi_reg_list* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  reg_list ; 
 int /*<<< orphan*/  reg_list_mutex ; 

__attribute__((used)) static void ipmi_new_smi(int if_num, struct device *device)
{
	dev_t dev = MKDEV(ipmi_major, if_num);
	struct ipmi_reg_list *entry;

	entry = kmalloc(sizeof(*entry), GFP_KERNEL);
	if (!entry) {
		pr_err("ipmi_devintf: Unable to create the ipmi class device link\n");
		return;
	}
	entry->dev = dev;

	mutex_lock(&reg_list_mutex);
	device_create(ipmi_class, device, dev, NULL, "ipmi%d", if_num);
	list_add(&entry->link, &reg_list);
	mutex_unlock(&reg_list_mutex);
}