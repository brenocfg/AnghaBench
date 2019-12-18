#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  os; void* fip_arg; void* fip; void* link_arg; void* link; } ;
typedef  TYPE_1__ sli4_t ;
typedef  int sli4_callback_e ;
typedef  int int32_t ;

/* Variables and functions */
#define  SLI4_CB_FIP 129 
#define  SLI4_CB_LINK 128 
 int SLI4_CB_MAX ; 
 int /*<<< orphan*/  ocs_log_err (int /*<<< orphan*/ *,char*,TYPE_1__*,int,void*) ; 
 int /*<<< orphan*/  ocs_log_test (int /*<<< orphan*/ ,char*,int) ; 

int32_t
sli_callback(sli4_t *sli4, sli4_callback_e which, void *func, void *arg)
{

	if (!sli4 || !func || (which >= SLI4_CB_MAX)) {
		ocs_log_err(NULL, "bad parameter sli4=%p which=%#x func=%p\n",
			    sli4, which, func);
		return -1;
	}

	switch (which) {
	case SLI4_CB_LINK:
		sli4->link = func;
		sli4->link_arg = arg;
		break;
	case SLI4_CB_FIP:
		sli4->fip = func;
		sli4->fip_arg = arg;
		break;
	default:
		ocs_log_test(sli4->os, "unknown callback %#x\n", which);
		return -1;
	}

	return 0;
}