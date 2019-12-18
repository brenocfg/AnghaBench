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
typedef  int /*<<< orphan*/  uint16_t ;
struct query_info {int dummy; } ;
struct module_qstate {int /*<<< orphan*/  mesh_info; TYPE_2__* env; } ;
struct TYPE_3__ {int count; } ;
struct mesh_state {TYPE_1__ super_set; int /*<<< orphan*/  cb_list; int /*<<< orphan*/  reply_list; } ;
struct mesh_area {scalar_t__ num_detached_states; } ;
struct TYPE_4__ {struct mesh_area* mesh; } ;

/* Variables and functions */
 int /*<<< orphan*/  log_assert (int) ; 
 int /*<<< orphan*/  mesh_add_sub (struct module_qstate*,struct query_info*,int /*<<< orphan*/ ,int,int,struct module_qstate**,struct mesh_state**) ; 
 int /*<<< orphan*/  mesh_state_attachment (int /*<<< orphan*/ ,struct mesh_state*) ; 

int mesh_attach_sub(struct module_qstate* qstate, struct query_info* qinfo,
        uint16_t qflags, int prime, int valrec, struct module_qstate** newq)
{
	struct mesh_area* mesh = qstate->env->mesh;
	struct mesh_state* sub = NULL;
	int was_detached;
	if(!mesh_add_sub(qstate, qinfo, qflags, prime, valrec, newq, &sub))
		return 0;
	was_detached = (sub->super_set.count == 0);
	if(!mesh_state_attachment(qstate->mesh_info, sub))
		return 0;
	/* if it was a duplicate  attachment, the count was not zero before */
	if(!sub->reply_list && !sub->cb_list && was_detached && 
		sub->super_set.count == 1) {
		/* it used to be detached, before this one got added */
		log_assert(mesh->num_detached_states > 0);
		mesh->num_detached_states--;
	}
	/* *newq will be run when inited after the current module stops */
	return 1;
}