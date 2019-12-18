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
struct agp_client {int dummy; } ;
typedef  int /*<<< orphan*/  pid_t ;
struct TYPE_2__ {int /*<<< orphan*/ * current_controller; } ;

/* Variables and functions */
 TYPE_1__ agp_fe ; 
 struct agp_client* agp_find_client_in_controller (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

struct agp_client *agp_find_client_by_pid(pid_t id)
{
	struct agp_client *temp;

	if (agp_fe.current_controller == NULL)
		return NULL;

	temp = agp_find_client_in_controller(agp_fe.current_controller, id);
	return temp;
}