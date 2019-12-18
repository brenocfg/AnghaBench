#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct query_info {int dummy; } ;
struct TYPE_10__ {size_t curmod; scalar_t__ return_rcode; scalar_t__ need_refetch; int /*<<< orphan*/  qinfo; int /*<<< orphan*/ ** minfo; } ;
struct TYPE_9__ {scalar_t__ count; } ;
struct mesh_state {scalar_t__ num_activated; TYPE_4__ s; TYPE_3__ sub_set; } ;
struct TYPE_8__ {size_t num; TYPE_1__** mod; } ;
struct mesh_area {TYPE_2__ mods; } ;
typedef  enum module_ext_state { ____Placeholder_module_ext_state } module_ext_state ;
typedef  enum module_ev { ____Placeholder_module_ev } module_ev ;
struct TYPE_7__ {int /*<<< orphan*/  (* clear ) (TYPE_4__*,size_t) ;int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ LDNS_RCODE_NOERROR ; 
 scalar_t__ LDNS_RCODE_SERVFAIL ; 
 scalar_t__ MESH_MAX_ACTIVATION ; 
 int /*<<< orphan*/  VERB_QUERY ; 
 int /*<<< orphan*/  fptr_ok (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fptr_whitelist_mod_clear (int /*<<< orphan*/  (*) (TYPE_4__*,size_t)) ; 
 int /*<<< orphan*/  log_err (char*,...) ; 
 int /*<<< orphan*/  log_query_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mesh_copy_qinfo (struct mesh_state*,struct query_info**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mesh_query_done (struct mesh_state*) ; 
 int /*<<< orphan*/  mesh_schedule_prefetch (struct mesh_area*,struct query_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mesh_state_delete (TYPE_4__*) ; 
 int /*<<< orphan*/  mesh_walk_supers (struct mesh_area*,struct mesh_state*) ; 
 int module_error ; 
 int module_event_moddone ; 
 int module_event_pass ; 
 int module_finished ; 
 int module_restart_next ; 
 int module_wait_module ; 
 int module_wait_subquery ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,size_t) ; 

__attribute__((used)) static int
mesh_continue(struct mesh_area* mesh, struct mesh_state* mstate,
	enum module_ext_state s, enum module_ev* ev)
{
	mstate->num_activated++;
	if(mstate->num_activated > MESH_MAX_ACTIVATION) {
		/* module is looping. Stop it. */
		log_err("internal error: looping module (%s) stopped",
			mesh->mods.mod[mstate->s.curmod]->name);
		log_query_info(0, "pass error for qstate",
			&mstate->s.qinfo);
		s = module_error;
	}
	if(s == module_wait_module || s == module_restart_next) {
		/* start next module */
		mstate->s.curmod++;
		if(mesh->mods.num == mstate->s.curmod) {
			log_err("Cannot pass to next module; at last module");
			log_query_info(VERB_QUERY, "pass error for qstate",
				&mstate->s.qinfo);
			mstate->s.curmod--;
			return mesh_continue(mesh, mstate, module_error, ev);
		}
		if(s == module_restart_next) {
			int curmod = mstate->s.curmod;
			for(; mstate->s.curmod < mesh->mods.num; 
				mstate->s.curmod++) {
				fptr_ok(fptr_whitelist_mod_clear(
					mesh->mods.mod[mstate->s.curmod]->clear));
				(*mesh->mods.mod[mstate->s.curmod]->clear)
					(&mstate->s, mstate->s.curmod);
				mstate->s.minfo[mstate->s.curmod] = NULL;
			}
			mstate->s.curmod = curmod;
		}
		*ev = module_event_pass;
		return 1;
	}
	if(s == module_wait_subquery && mstate->sub_set.count == 0) {
		log_err("module cannot wait for subquery, subquery list empty");
		log_query_info(VERB_QUERY, "pass error for qstate",
			&mstate->s.qinfo);
		s = module_error;
	}
	if(s == module_error && mstate->s.return_rcode == LDNS_RCODE_NOERROR) {
		/* error is bad, handle pass back up below */
		mstate->s.return_rcode = LDNS_RCODE_SERVFAIL;
	}
	if(s == module_error) {
		mesh_query_done(mstate);
		mesh_walk_supers(mesh, mstate);
		mesh_state_delete(&mstate->s);
		return 0;
	}
	if(s == module_finished) {
		if(mstate->s.curmod == 0) {
			struct query_info* qinfo = NULL;
			uint16_t qflags;

			mesh_query_done(mstate);
			mesh_walk_supers(mesh, mstate);

			/* If the answer to the query needs to be refetched
			 * from an external DNS server, we'll need to schedule
			 * a prefetch after removing the current state, so
			 * we need to make a copy of the query info here. */
			if(mstate->s.need_refetch)
				mesh_copy_qinfo(mstate, &qinfo, &qflags);

			mesh_state_delete(&mstate->s);
			if(qinfo) {
				mesh_schedule_prefetch(mesh, qinfo, qflags,
					0, 1);
			}
			return 0;
		}
		/* pass along the locus of control */
		mstate->s.curmod --;
		*ev = module_event_moddone;
		return 1;
	}
	return 0;
}