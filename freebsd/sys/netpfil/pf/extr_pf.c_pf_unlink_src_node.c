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
struct TYPE_4__ {TYPE_1__* ptr; } ;
struct pf_src_node {TYPE_2__ rule; int /*<<< orphan*/  af; int /*<<< orphan*/  addr; } ;
struct TYPE_3__ {int /*<<< orphan*/  src_nodes; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (struct pf_src_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PF_HASHROW_ASSERT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * V_pf_srchash ; 
 int /*<<< orphan*/  counter_u64_add (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  entry ; 
 size_t pf_hashsrc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
pf_unlink_src_node(struct pf_src_node *src)
{

	PF_HASHROW_ASSERT(&V_pf_srchash[pf_hashsrc(&src->addr, src->af)]);
	LIST_REMOVE(src, entry);
	if (src->rule.ptr)
		counter_u64_add(src->rule.ptr->src_nodes, -1);
}