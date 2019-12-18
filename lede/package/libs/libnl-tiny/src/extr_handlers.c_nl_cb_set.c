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
struct nl_cb {void** cb_args; int /*<<< orphan*/ * cb_set; } ;
typedef  int /*<<< orphan*/  nl_recvmsg_msg_cb_t ;
typedef  enum nl_cb_type { ____Placeholder_nl_cb_type } nl_cb_type ;
typedef  enum nl_cb_kind { ____Placeholder_nl_cb_kind } nl_cb_kind ;

/* Variables and functions */
 int NLE_RANGE ; 
 int NL_CB_CUSTOM ; 
 int NL_CB_KIND_MAX ; 
 int NL_CB_TYPE_MAX ; 

int nl_cb_set(struct nl_cb *cb, enum nl_cb_type type, enum nl_cb_kind kind,
	      nl_recvmsg_msg_cb_t func, void *arg)
{
	if (type < 0 || type > NL_CB_TYPE_MAX)
		return -NLE_RANGE;

	if (kind < 0 || kind > NL_CB_KIND_MAX)
		return -NLE_RANGE;

	if (kind == NL_CB_CUSTOM) {
		cb->cb_set[type] = func;
		cb->cb_args[type] = arg;
	}

	return 0;
}