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
struct auth_xfer {int /*<<< orphan*/  allow_notify_list; struct auth_xfer* task_transfer; scalar_t__ chunks_first; int /*<<< orphan*/  timer; int /*<<< orphan*/  cp; int /*<<< orphan*/  masters; struct auth_xfer* task_probe; struct auth_xfer* task_nextprobe; struct auth_xfer* name; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  auth_chunks_delete (struct auth_xfer*) ; 
 int /*<<< orphan*/  auth_free_masters (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  comm_point_delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  comm_timer_delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct auth_xfer*) ; 
 int /*<<< orphan*/  lock_basic_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
auth_xfer_delete(struct auth_xfer* xfr)
{
	if(!xfr) return;
	lock_basic_destroy(&xfr->lock);
	free(xfr->name);
	if(xfr->task_nextprobe) {
		comm_timer_delete(xfr->task_nextprobe->timer);
		free(xfr->task_nextprobe);
	}
	if(xfr->task_probe) {
		auth_free_masters(xfr->task_probe->masters);
		comm_point_delete(xfr->task_probe->cp);
		comm_timer_delete(xfr->task_probe->timer);
		free(xfr->task_probe);
	}
	if(xfr->task_transfer) {
		auth_free_masters(xfr->task_transfer->masters);
		comm_point_delete(xfr->task_transfer->cp);
		comm_timer_delete(xfr->task_transfer->timer);
		if(xfr->task_transfer->chunks_first) {
			auth_chunks_delete(xfr->task_transfer);
		}
		free(xfr->task_transfer);
	}
	auth_free_masters(xfr->allow_notify_list);
	free(xfr);
}