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
struct radius_server_data {int dummy; } ;
struct radius_client {int /*<<< orphan*/  pending_dac_disconnect_req; int /*<<< orphan*/  pending_dac_coa_req; struct radius_client* shared_secret; int /*<<< orphan*/  sessions; struct radius_client* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  os_free (struct radius_client*) ; 
 int /*<<< orphan*/  radius_msg_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radius_server_free_sessions (struct radius_server_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void radius_server_free_clients(struct radius_server_data *data,
				       struct radius_client *clients)
{
	struct radius_client *client, *prev;

	client = clients;
	while (client) {
		prev = client;
		client = client->next;

		radius_server_free_sessions(data, prev->sessions);
		os_free(prev->shared_secret);
		radius_msg_free(prev->pending_dac_coa_req);
		radius_msg_free(prev->pending_dac_disconnect_req);
		os_free(prev);
	}
}