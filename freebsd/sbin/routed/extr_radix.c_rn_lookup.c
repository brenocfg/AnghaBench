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
struct radix_node_head {TYPE_1__* rnh_treetop; } ;
struct radix_node {scalar_t__ rn_key; scalar_t__ rn_mask; struct radix_node* rn_dupedkey; } ;
typedef  scalar_t__ caddr_t ;
struct TYPE_2__ {int /*<<< orphan*/  rn_off; } ;

/* Variables and functions */
 struct radix_node* rn_addmask (void*,int,int /*<<< orphan*/ ) ; 
 struct radix_node* rn_match (void*,struct radix_node_head*) ; 

__attribute__((used)) static struct radix_node *
rn_lookup(void *v_arg, void *m_arg, struct radix_node_head *head)
{
	struct radix_node *x;
	caddr_t netmask = 0;

	if (m_arg) {
		if ((x = rn_addmask(m_arg, 1,
		    head->rnh_treetop->rn_off)) == NULL)
			return (0);
		netmask = x->rn_key;
	}
	x = rn_match(v_arg, head);
	if (x && netmask) {
		while (x && x->rn_mask != netmask)
			x = x->rn_dupedkey;
	}
	return x;
}