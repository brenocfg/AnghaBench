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
struct tcp_req_open_item {struct tcp_req_open_item* next; struct mesh_state* mesh_state; } ;
struct tcp_req_info {int /*<<< orphan*/  num_open_req; struct tcp_req_open_item* open_req_list; } ;
struct mesh_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct tcp_req_open_item*) ; 

void
tcp_req_info_remove_mesh_state(struct tcp_req_info* req, struct mesh_state* m)
{
	struct tcp_req_open_item* open, *prev = NULL;
	if(!req || !m) return;
	open = req->open_req_list;
	while(open) {
		if(open->mesh_state == m) {
			struct tcp_req_open_item* next;
			if(prev) prev->next = open->next;
			else req->open_req_list = open->next;
			/* caller has to manage the mesh state reply entry */
			next = open->next;
			free(open);
			req->num_open_req --;

			/* prev = prev; */
			open = next;
			continue;
		}
		prev = open;
		open = open->next;
	}
}