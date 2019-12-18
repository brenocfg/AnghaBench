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
struct genl_family_op {int o_id; int o_flags; int /*<<< orphan*/  o_list; } ;
struct genl_family {int /*<<< orphan*/  ce_mask; int /*<<< orphan*/  gf_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  FAMILY_ATTR_OPS ; 
 int NLE_NOMEM ; 
 struct genl_family_op* calloc (int,int) ; 
 int /*<<< orphan*/  nl_list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int genl_family_add_op(struct genl_family *family, int id, int flags)
{
	struct genl_family_op *op;

	op = calloc(1, sizeof(*op));
	if (op == NULL)
		return -NLE_NOMEM;

	op->o_id = id;
	op->o_flags = flags;

	nl_list_add_tail(&op->o_list, &family->gf_ops);
	family->ce_mask |= FAMILY_ATTR_OPS;

	return 0;
}