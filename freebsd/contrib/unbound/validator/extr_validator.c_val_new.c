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
struct val_qstate {int /*<<< orphan*/  state; } ;
struct module_qstate {struct val_qstate** minfo; int /*<<< orphan*/  region; } ;

/* Variables and functions */
 int /*<<< orphan*/  VAL_INIT_STATE ; 
 int /*<<< orphan*/  log_assert (int) ; 
 int /*<<< orphan*/  memset (struct val_qstate*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ regional_alloc (int /*<<< orphan*/ ,int) ; 
 struct val_qstate* val_new_getmsg (struct module_qstate*,struct val_qstate*) ; 

__attribute__((used)) static struct val_qstate*
val_new(struct module_qstate* qstate, int id)
{
	struct val_qstate* vq = (struct val_qstate*)regional_alloc(
		qstate->region, sizeof(*vq));
	log_assert(!qstate->minfo[id]);
	if(!vq)
		return NULL;
	memset(vq, 0, sizeof(*vq));
	qstate->minfo[id] = vq;
	vq->state = VAL_INIT_STATE;
	return val_new_getmsg(qstate, vq);
}