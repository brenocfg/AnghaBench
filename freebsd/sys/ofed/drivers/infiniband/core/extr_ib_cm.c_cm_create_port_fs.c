#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct cm_port {int /*<<< orphan*/  port_obj; TYPE_3__* counter_group; int /*<<< orphan*/  port_num; TYPE_2__* cm_dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  obj; } ;
struct TYPE_5__ {TYPE_1__* device; } ;
struct TYPE_4__ {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int CM_COUNTER_GROUPS ; 
 int /*<<< orphan*/  cm_counter_obj_type ; 
 int /*<<< orphan*/  cm_port_obj_type ; 
 int /*<<< orphan*/ * counter_group_names ; 
 int /*<<< orphan*/  kfree (struct cm_port*) ; 
 int kobject_init_and_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cm_create_port_fs(struct cm_port *port)
{
	int i, ret;

	ret = kobject_init_and_add(&port->port_obj, &cm_port_obj_type,
				   &port->cm_dev->device->kobj,
				   "%d", port->port_num);
	if (ret) {
		kfree(port);
		return ret;
	}

	for (i = 0; i < CM_COUNTER_GROUPS; i++) {
		ret = kobject_init_and_add(&port->counter_group[i].obj,
					   &cm_counter_obj_type,
					   &port->port_obj,
					   "%s", counter_group_names[i]);
		if (ret)
			goto error;
	}

	return 0;

error:
	while (i--)
		kobject_put(&port->counter_group[i].obj);
	kobject_put(&port->port_obj);
	return ret;

}