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
struct agp_controller {struct agp_controller* next; } ;
typedef  int /*<<< orphan*/  pid_t ;
struct TYPE_2__ {struct agp_controller* controllers; } ;

/* Variables and functions */
 TYPE_1__ agp_fe ; 
 int /*<<< orphan*/ * agp_find_client_in_controller (struct agp_controller*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct agp_controller *agp_find_controller_for_client(pid_t id)
{
	struct agp_controller *controller;

	controller = agp_fe.controllers;

	while (controller != NULL) {
		if ((agp_find_client_in_controller(controller, id)) != NULL)
			return controller;
		controller = controller->next;
	}

	return NULL;
}