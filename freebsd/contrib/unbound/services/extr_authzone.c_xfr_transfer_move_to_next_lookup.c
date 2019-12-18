#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct module_env {TYPE_1__* cfg; } ;
struct auth_xfer {TYPE_2__* task_transfer; } ;
struct TYPE_6__ {struct TYPE_6__* next; } ;
struct TYPE_5__ {int lookup_aaaa; TYPE_3__* lookup_target; } ;
struct TYPE_4__ {int /*<<< orphan*/  do_ip4; scalar_t__ do_ip6; } ;

/* Variables and functions */

__attribute__((used)) static void
xfr_transfer_move_to_next_lookup(struct auth_xfer* xfr, struct module_env* env)
{
	if(!xfr->task_transfer->lookup_target)
		return; /* already at end of list */
	if(!xfr->task_transfer->lookup_aaaa && env->cfg->do_ip6) {
		/* move to lookup AAAA */
		xfr->task_transfer->lookup_aaaa = 1;
		return;
	}
	xfr->task_transfer->lookup_target = 
		xfr->task_transfer->lookup_target->next;
	xfr->task_transfer->lookup_aaaa = 0;
	if(!env->cfg->do_ip4 && xfr->task_transfer->lookup_target!=NULL)
		xfr->task_transfer->lookup_aaaa = 1;
}