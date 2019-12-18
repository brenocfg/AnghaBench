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
struct nl_object_ops {int oo_size; int /*<<< orphan*/  (* oo_constructor ) (struct nl_object*) ;} ;
struct nl_object {int ce_refcnt; struct nl_object_ops* ce_ops; int /*<<< orphan*/  ce_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  NL_DBG (int,char*,struct nl_object*) ; 
 struct nl_object* calloc (int,int) ; 
 int /*<<< orphan*/  nl_init_list_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct nl_object*) ; 

struct nl_object *nl_object_alloc(struct nl_object_ops *ops)
{
	struct nl_object *new;

	if (ops->oo_size < sizeof(*new))
		BUG();

	new = calloc(1, ops->oo_size);
	if (!new)
		return NULL;

	new->ce_refcnt = 1;
	nl_init_list_head(&new->ce_list);

	new->ce_ops = ops;
	if (ops->oo_constructor)
		ops->oo_constructor(new);

	NL_DBG(4, "Allocated new object %p\n", new);

	return new;
}