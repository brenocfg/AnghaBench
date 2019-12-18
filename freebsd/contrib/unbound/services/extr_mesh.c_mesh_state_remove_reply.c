#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ count; } ;
struct mesh_state {int /*<<< orphan*/  cb_list; struct mesh_reply* reply_list; TYPE_2__ super_set; } ;
struct TYPE_3__ {struct comm_point* c; } ;
struct mesh_reply {struct mesh_reply* next; TYPE_1__ query_reply; } ;
struct mesh_area {scalar_t__ num_reply_states; int /*<<< orphan*/  num_detached_states; int /*<<< orphan*/  num_reply_addrs; } ;
struct comm_point {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  log_assert (int) ; 

void mesh_state_remove_reply(struct mesh_area* mesh, struct mesh_state* m,
	struct comm_point* cp)
{
	struct mesh_reply* n, *prev = NULL;
	n = m->reply_list;
	/* when in mesh_cleanup, it sets the reply_list to NULL, so that
	 * there is no accounting twice */
	if(!n) return; /* nothing to remove, also no accounting needed */
	while(n) {
		if(n->query_reply.c == cp) {
			/* unlink it */
			if(prev) prev->next = n->next;
			else m->reply_list = n->next;
			/* delete it, but allocated in m region */
			mesh->num_reply_addrs--;

			/* prev = prev; */
			n = n->next;
			continue;
		}
		prev = n;
		n = n->next;
	}
	/* it was not detached (because it had a reply list), could be now */
	if(!m->reply_list && !m->cb_list
		&& m->super_set.count == 0) {
		mesh->num_detached_states++;
	}
	/* if not replies any more in mstate, it is no longer a reply_state */
	if(!m->reply_list && !m->cb_list) {
		log_assert(mesh->num_reply_states > 0);
		mesh->num_reply_states--;
	}
}