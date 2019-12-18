#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct agp_file_private {int /*<<< orphan*/  access_flags; int /*<<< orphan*/  my_pid; } ;
struct agp_controller {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  agp_in_use; } ;
struct TYPE_4__ {int backend_acquired; int /*<<< orphan*/ * current_controller; } ;

/* Variables and functions */
 int /*<<< orphan*/  AGP_FF_ALLOW_CONTROLLER ; 
 int /*<<< orphan*/  AGP_FF_IS_CONTROLLER ; 
 int /*<<< orphan*/  AGP_FF_IS_VALID ; 
 int /*<<< orphan*/  DBG (char*) ; 
 int EBUSY ; 
 int ENODEV ; 
 int ENOMEM ; 
 int EPERM ; 
 int /*<<< orphan*/  agp_backend_release (TYPE_2__*) ; 
 TYPE_2__* agp_bridge ; 
 int /*<<< orphan*/  agp_controller_make_current (struct agp_controller*) ; 
 struct agp_controller* agp_create_controller (int /*<<< orphan*/ ) ; 
 TYPE_1__ agp_fe ; 
 struct agp_controller* agp_find_controller_by_pid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  agp_insert_controller (struct agp_controller*) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int agpioc_acquire_wrap(struct agp_file_private *priv)
{
	struct agp_controller *controller;

	DBG("");

	if (!(test_bit(AGP_FF_ALLOW_CONTROLLER, &priv->access_flags)))
		return -EPERM;

	if (agp_fe.current_controller != NULL)
		return -EBUSY;

	if (!agp_bridge)
		return -ENODEV;

        if (atomic_read(&agp_bridge->agp_in_use))
                return -EBUSY;

	atomic_inc(&agp_bridge->agp_in_use);

	agp_fe.backend_acquired = true;

	controller = agp_find_controller_by_pid(priv->my_pid);

	if (controller != NULL) {
		agp_controller_make_current(controller);
	} else {
		controller = agp_create_controller(priv->my_pid);

		if (controller == NULL) {
			agp_fe.backend_acquired = false;
			agp_backend_release(agp_bridge);
			return -ENOMEM;
		}
		agp_insert_controller(controller);
		agp_controller_make_current(controller);
	}

	set_bit(AGP_FF_IS_CONTROLLER, &priv->access_flags);
	set_bit(AGP_FF_IS_VALID, &priv->access_flags);
	return 0;
}