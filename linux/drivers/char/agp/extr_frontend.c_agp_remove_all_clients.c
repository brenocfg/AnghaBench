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
struct agp_file_private {int /*<<< orphan*/  access_flags; } ;
struct agp_controller {struct agp_client* clients; } ;
struct agp_client {struct agp_client* next; int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  AGP_FF_IS_CLIENT ; 
 int /*<<< orphan*/  AGP_FF_IS_VALID ; 
 struct agp_file_private* agp_find_private (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  agp_remove_seg_from_client (struct agp_client*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct agp_client*) ; 

__attribute__((used)) static void agp_remove_all_clients(struct agp_controller *controller)
{
	struct agp_client *client;
	struct agp_client *temp;

	client = controller->clients;

	while (client) {
		struct agp_file_private *priv;

		temp = client;
		agp_remove_seg_from_client(temp);
		priv = agp_find_private(temp->pid);

		if (priv != NULL) {
			clear_bit(AGP_FF_IS_VALID, &priv->access_flags);
			clear_bit(AGP_FF_IS_CLIENT, &priv->access_flags);
		}
		client = client->next;
		kfree(temp);
	}
}