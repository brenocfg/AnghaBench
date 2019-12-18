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
struct comm_signal {int /*<<< orphan*/  cb_arg; int /*<<< orphan*/  (* callback ) (int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  base; } ;

/* Variables and functions */
 short UB_EV_SIGNAL ; 
 int /*<<< orphan*/  fptr_ok (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fptr_whitelist_comm_signal (int /*<<< orphan*/  (*) (int,int /*<<< orphan*/ )) ; 
 int /*<<< orphan*/  stub1 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ub_comm_base_now (int /*<<< orphan*/ ) ; 

void 
comm_signal_callback(int sig, short event, void* arg)
{
	struct comm_signal* comsig = (struct comm_signal*)arg;
	if(!(event & UB_EV_SIGNAL))
		return;
	ub_comm_base_now(comsig->base);
	fptr_ok(fptr_whitelist_comm_signal(comsig->callback));
	(*comsig->callback)(sig, comsig->cb_arg);
}