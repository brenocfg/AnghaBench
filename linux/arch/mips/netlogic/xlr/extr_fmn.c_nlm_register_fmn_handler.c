#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {void (* action ) (int,int,int,int,struct nlm_fmn_msg*,void*) ;void* arg; } ;

/* Variables and functions */
 TYPE_1__* msg_handlers ; 
 int /*<<< orphan*/  pr_debug (char*,int,int) ; 
 int /*<<< orphan*/  smp_wmb () ; 

int nlm_register_fmn_handler(int start_stnid, int end_stnid,
	void (*action)(int, int, int, int, struct nlm_fmn_msg *, void *),
	void *arg)
{
	int sstnid;

	for (sstnid = start_stnid; sstnid <= end_stnid; sstnid++) {
		msg_handlers[sstnid].arg = arg;
		smp_wmb();
		msg_handlers[sstnid].action = action;
	}
	pr_debug("Registered FMN msg handler for stnid %d-%d\n",
			start_stnid, end_stnid);
	return 0;
}