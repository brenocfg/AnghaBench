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
struct counter_signal_ext_unit {struct counter_signal_ext const* ext; struct counter_signal* signal; } ;
struct counter_signal_ext {scalar_t__ write; scalar_t__ read; int /*<<< orphan*/  name; } ;
struct counter_signal {size_t num_ext; struct counter_signal_ext* ext; } ;
struct counter_device_attr_group {int /*<<< orphan*/  attr_list; } ;
struct counter_attr_parm {char* prefix; struct counter_signal_ext_unit* component; int /*<<< orphan*/ * store; int /*<<< orphan*/ * show; int /*<<< orphan*/  name; struct counter_device_attr_group* group; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int counter_attribute_create (struct counter_attr_parm*) ; 
 int /*<<< orphan*/  counter_device_attr_list_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * counter_signal_ext_show ; 
 int /*<<< orphan*/ * counter_signal_ext_store ; 
 int /*<<< orphan*/  kfree (struct counter_signal_ext_unit*) ; 
 struct counter_signal_ext_unit* kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int counter_signal_ext_register(
	struct counter_device_attr_group *const group,
	struct counter_signal *const signal)
{
	const size_t num_ext = signal->num_ext;
	size_t i;
	const struct counter_signal_ext *ext;
	struct counter_signal_ext_unit *signal_ext_comp;
	struct counter_attr_parm parm;
	int err;

	/* Create an attribute for each extension */
	for (i = 0 ; i < num_ext; i++) {
		ext = signal->ext + i;

		/* Allocate signal_ext attribute component */
		signal_ext_comp = kmalloc(sizeof(*signal_ext_comp), GFP_KERNEL);
		if (!signal_ext_comp) {
			err = -ENOMEM;
			goto err_free_attr_list;
		}
		signal_ext_comp->signal = signal;
		signal_ext_comp->ext = ext;

		/* Allocate a Counter device attribute */
		parm.group = group;
		parm.prefix = "";
		parm.name = ext->name;
		parm.show = (ext->read) ? counter_signal_ext_show : NULL;
		parm.store = (ext->write) ? counter_signal_ext_store : NULL;
		parm.component = signal_ext_comp;
		err = counter_attribute_create(&parm);
		if (err) {
			kfree(signal_ext_comp);
			goto err_free_attr_list;
		}
	}

	return 0;

err_free_attr_list:
	counter_device_attr_list_free(&group->attr_list);
	return err;
}