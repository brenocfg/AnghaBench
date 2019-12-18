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
struct nl_cb {void* cb_err_arg; int /*<<< orphan*/  cb_err; } ;
typedef  int /*<<< orphan*/  nl_recvmsg_err_cb_t ;
typedef  enum nl_cb_kind { ____Placeholder_nl_cb_kind } nl_cb_kind ;

/* Variables and functions */
 int NLE_RANGE ; 
 int NL_CB_CUSTOM ; 
 int NL_CB_KIND_MAX ; 

int nl_cb_err(struct nl_cb *cb, enum nl_cb_kind kind,
	      nl_recvmsg_err_cb_t func, void *arg)
{
	if (kind < 0 || kind > NL_CB_KIND_MAX)
		return -NLE_RANGE;

	if (kind == NL_CB_CUSTOM) {
		cb->cb_err = func;
		cb->cb_err_arg = arg;
	}

	return 0;
}