#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  region; TYPE_3__* env; int /*<<< orphan*/ * ext_state; int /*<<< orphan*/ ** minfo; } ;
struct mesh_state {TYPE_4__ s; struct mesh_cb* cb_list; struct mesh_reply* reply_list; int /*<<< orphan*/  replies_sent; } ;
struct mesh_reply {int /*<<< orphan*/  query_reply; struct mesh_reply* next; } ;
struct mesh_cb {int /*<<< orphan*/  cb_arg; int /*<<< orphan*/  (* cb ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;struct mesh_cb* next; } ;
struct TYPE_7__ {int num; TYPE_1__** mod; } ;
struct mesh_area {TYPE_2__ mods; int /*<<< orphan*/  num_reply_addrs; } ;
struct TYPE_8__ {int /*<<< orphan*/  alloc; struct mesh_area* mesh; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* clear ) (TYPE_4__*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_RCODE_SERVFAIL ; 
 int /*<<< orphan*/  alloc_reg_release (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  comm_point_drop_reply (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fptr_ok (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fptr_whitelist_mesh_cb (int /*<<< orphan*/  (*) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ )) ; 
 int /*<<< orphan*/  fptr_whitelist_mod_clear (int /*<<< orphan*/  (*) (TYPE_4__*,int)) ; 
 int /*<<< orphan*/  module_finished ; 
 int /*<<< orphan*/  sec_status_unchecked ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_4__*,int) ; 

void 
mesh_state_cleanup(struct mesh_state* mstate)
{
	struct mesh_area* mesh;
	int i;
	if(!mstate)
		return;
	mesh = mstate->s.env->mesh;
	/* drop unsent replies */
	if(!mstate->replies_sent) {
		struct mesh_reply* rep = mstate->reply_list;
		struct mesh_cb* cb;
		/* in tcp_req_info, the mstates linked are removed, but
		 * the reply_list is now NULL, so the remove-from-empty-list
		 * takes no time and also it does not do the mesh accounting */
		mstate->reply_list = NULL;
		for(; rep; rep=rep->next) {
			comm_point_drop_reply(&rep->query_reply);
			mesh->num_reply_addrs--;
		}
		while((cb = mstate->cb_list)!=NULL) {
			mstate->cb_list = cb->next;
			fptr_ok(fptr_whitelist_mesh_cb(cb->cb));
			(*cb->cb)(cb->cb_arg, LDNS_RCODE_SERVFAIL, NULL,
				sec_status_unchecked, NULL, 0);
			mesh->num_reply_addrs--;
		}
	}

	/* de-init modules */
	for(i=0; i<mesh->mods.num; i++) {
		fptr_ok(fptr_whitelist_mod_clear(mesh->mods.mod[i]->clear));
		(*mesh->mods.mod[i]->clear)(&mstate->s, i);
		mstate->s.minfo[i] = NULL;
		mstate->s.ext_state[i] = module_finished;
	}
	alloc_reg_release(mstate->s.env->alloc, mstate->s.region);
}