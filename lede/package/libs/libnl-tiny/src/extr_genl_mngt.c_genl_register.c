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
struct nl_cache_ops {scalar_t__ co_protocol; scalar_t__ co_hdrsize; TYPE_2__* co_genl; int /*<<< orphan*/  co_msg_parser; TYPE_1__* co_msgtypes; } ;
struct TYPE_4__ {int /*<<< orphan*/  o_list; int /*<<< orphan*/  o_family; int /*<<< orphan*/  o_name; struct nl_cache_ops* o_cache_ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  mt_id; int /*<<< orphan*/  mt_name; } ;

/* Variables and functions */
 scalar_t__ GENL_HDRSIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ NETLINK_GENERIC ; 
 int NLE_INVAL ; 
 int NLE_PROTO_MISMATCH ; 
 int /*<<< orphan*/  genl_msg_parser ; 
 int /*<<< orphan*/  genl_ops_list ; 
 int nl_cache_mngt_register (struct nl_cache_ops*) ; 
 int /*<<< orphan*/  nl_list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int genl_register(struct nl_cache_ops *ops)
{
	int err;

	if (ops->co_protocol != NETLINK_GENERIC) {
		err = -NLE_PROTO_MISMATCH;
		goto errout;
	}

	if (ops->co_hdrsize < GENL_HDRSIZE(0)) {
		err = -NLE_INVAL;
		goto errout;
	}

	if (ops->co_genl == NULL) {
		err = -NLE_INVAL;
		goto errout;
	}

	ops->co_genl->o_cache_ops = ops;
	ops->co_genl->o_name = ops->co_msgtypes[0].mt_name;
	ops->co_genl->o_family = ops->co_msgtypes[0].mt_id;
	ops->co_msg_parser = genl_msg_parser;

	/* FIXME: check for dup */

	nl_list_add_tail(&ops->co_genl->o_list, &genl_ops_list);

	err = nl_cache_mngt_register(ops);
errout:
	return err;
}