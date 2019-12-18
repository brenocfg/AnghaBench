#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct counter_ext_unit {TYPE_1__* ext; } ;
struct counter_device_attr_group {int /*<<< orphan*/  attr_list; } ;
struct counter_device {size_t num_ext; TYPE_1__* ext; } ;
struct counter_attr_parm {char* prefix; struct counter_ext_unit* component; int /*<<< orphan*/ * store; int /*<<< orphan*/ * show; int /*<<< orphan*/  name; struct counter_device_attr_group* group; } ;
struct TYPE_2__ {scalar_t__ write; scalar_t__ read; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int counter_attribute_create (struct counter_attr_parm*) ; 
 int /*<<< orphan*/  counter_device_attr_list_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * counter_device_ext_show ; 
 int /*<<< orphan*/ * counter_device_ext_store ; 
 int /*<<< orphan*/  kfree (struct counter_ext_unit*) ; 
 struct counter_ext_unit* kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int counter_device_ext_register(
	struct counter_device_attr_group *const group,
	struct counter_device *const counter)
{
	size_t i;
	struct counter_ext_unit *ext_comp;
	struct counter_attr_parm parm;
	int err;

	/* Create an attribute for each extension */
	for (i = 0 ; i < counter->num_ext; i++) {
		/* Allocate extension attribute component */
		ext_comp = kmalloc(sizeof(*ext_comp), GFP_KERNEL);
		if (!ext_comp) {
			err = -ENOMEM;
			goto err_free_attr_list;
		}

		ext_comp->ext = counter->ext + i;

		/* Allocate extension attribute */
		parm.group = group;
		parm.prefix = "";
		parm.name = counter->ext[i].name;
		parm.show = (counter->ext[i].read) ? counter_device_ext_show : NULL;
		parm.store = (counter->ext[i].write) ? counter_device_ext_store : NULL;
		parm.component = ext_comp;
		err = counter_attribute_create(&parm);
		if (err) {
			kfree(ext_comp);
			goto err_free_attr_list;
		}
	}

	return 0;

err_free_attr_list:
	counter_device_attr_list_free(&group->attr_list);
	return err;
}