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
struct radix_node {void* rn_key; void* rn_mask; struct radix_node* rn_dupedkey; } ;
struct radix_head {TYPE_1__* rnh_treetop; int /*<<< orphan*/  rnh_masks; } ;
typedef  void* caddr_t ;
struct TYPE_2__ {int /*<<< orphan*/  rn_offset; } ;

/* Variables and functions */
 scalar_t__ LEN (void*) ; 
 scalar_t__ bcmp (void*,void*,scalar_t__) ; 
 struct radix_node* rn_addmask (void*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct radix_node* rn_match (void*,struct radix_head*) ; 

struct radix_node *
rn_lookup(void *v_arg, void *m_arg, struct radix_head *head)
{
	struct radix_node *x;
	caddr_t netmask;

	if (m_arg != NULL) {
		/*
		 * Most common case: search exact prefix/mask
		 */
		x = rn_addmask(m_arg, head->rnh_masks, 1,
		    head->rnh_treetop->rn_offset);
		if (x == NULL)
			return (NULL);
		netmask = x->rn_key;

		x = rn_match(v_arg, head);

		while (x != NULL && x->rn_mask != netmask)
			x = x->rn_dupedkey;

		return (x);
	}

	/*
	 * Search for host address.
	 */
	if ((x = rn_match(v_arg, head)) == NULL)
		return (NULL);

	/* Check if found key is the same */
	if (LEN(x->rn_key) != LEN(v_arg) || bcmp(x->rn_key, v_arg, LEN(v_arg)))
		return (NULL);

	/* Check if this is not host route */
	if (x->rn_mask != NULL)
		return (NULL);

	return (x);
}