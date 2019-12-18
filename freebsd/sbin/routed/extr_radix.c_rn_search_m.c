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
struct radix_node {scalar_t__ rn_b; int rn_bmask; size_t rn_off; struct radix_node* rn_l; struct radix_node* rn_r; } ;
typedef  int* caddr_t ;

/* Variables and functions */

__attribute__((used)) static struct radix_node *
rn_search_m(void *v_arg,
	    struct radix_node *head,
	    void *m_arg)
{
	struct radix_node *x;
	caddr_t v = v_arg, m = m_arg;

	for (x = head; x->rn_b >= 0;) {
		if ((x->rn_bmask & m[x->rn_off]) &&
		    (x->rn_bmask & v[x->rn_off]))
			x = x->rn_r;
		else
			x = x->rn_l;
	}
	return x;
}