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
struct counter_size_unit {size_t size; } ;
struct counter_device_attr_group {int dummy; } ;
struct counter_attr_parm {char* prefix; char* name; struct counter_size_unit* component; int /*<<< orphan*/ * store; int /*<<< orphan*/  show; struct counter_device_attr_group* group; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int counter_attribute_create (struct counter_attr_parm*) ; 
 int /*<<< orphan*/  counter_device_attr_size_show ; 
 int /*<<< orphan*/  kfree (struct counter_size_unit*) ; 
 struct counter_size_unit* kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int counter_size_attribute_create(
	struct counter_device_attr_group *const group,
	const size_t size, const char *const name)
{
	struct counter_size_unit *size_comp;
	struct counter_attr_parm parm;
	int err;

	/* Allocate size attribute component */
	size_comp = kmalloc(sizeof(*size_comp), GFP_KERNEL);
	if (!size_comp)
		return -ENOMEM;
	size_comp->size = size;

	parm.group = group;
	parm.prefix = "";
	parm.name = name;
	parm.show = counter_device_attr_size_show;
	parm.store = NULL;
	parm.component = size_comp;
	err = counter_attribute_create(&parm);
	if (err)
		goto err_free_size_comp;

	return 0;

err_free_size_comp:
	kfree(size_comp);
	return err;
}