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
struct radix_node {scalar_t__ rn_bit; int rn_bmask; size_t rn_offset; struct radix_node* rn_left; struct radix_node* rn_right; } ;
typedef  int* caddr_t ;

/* Variables and functions */

__attribute__((used)) static struct radix_node *
rn_search(void *v_arg, struct radix_node *head)
{
	struct radix_node *x;
	caddr_t v;

	for (x = head, v = v_arg; x->rn_bit >= 0;) {
		if (x->rn_bmask & v[x->rn_offset])
			x = x->rn_right;
		else
			x = x->rn_left;
	}
	return (x);
}