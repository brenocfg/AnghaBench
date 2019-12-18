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
struct module_qstate {int /*<<< orphan*/ ** minfo; } ;
struct iter_qstate {scalar_t__* target_count; scalar_t__ num_current_queries; int /*<<< orphan*/  outlist; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (scalar_t__*) ; 
 int /*<<< orphan*/  outbound_list_clear (int /*<<< orphan*/ *) ; 

void 
iter_clear(struct module_qstate* qstate, int id)
{
	struct iter_qstate* iq;
	if(!qstate)
		return;
	iq = (struct iter_qstate*)qstate->minfo[id];
	if(iq) {
		outbound_list_clear(&iq->outlist);
		if(iq->target_count && --iq->target_count[0] == 0)
			free(iq->target_count);
		iq->num_current_queries = 0;
	}
	qstate->minfo[id] = NULL;
}