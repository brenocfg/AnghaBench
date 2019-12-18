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
struct agp_controller {struct agp_client* clients; } ;
struct agp_client {scalar_t__ pid; struct agp_client* next; } ;
typedef  scalar_t__ pid_t ;

/* Variables and functions */

__attribute__((used)) static struct agp_client
*agp_find_client_in_controller(struct agp_controller *controller, pid_t id)
{
	struct agp_client *client;

	if (controller == NULL)
		return NULL;

	client = controller->clients;

	while (client != NULL) {
		if (client->pid == id)
			return client;
		client = client->next;
	}

	return NULL;
}