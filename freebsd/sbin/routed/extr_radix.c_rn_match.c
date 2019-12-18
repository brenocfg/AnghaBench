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
typedef  int u_char ;
struct radix_node_head {struct radix_node* rnh_treetop; } ;
struct radix_node {int rn_off; int rn_b; int rn_bmask; scalar_t__ rn_mask; int* rn_key; int rn_flags; struct radix_node* rn_dupedkey; struct radix_mask* rn_mklist; struct radix_node* rn_p; struct radix_node* rn_l; struct radix_node* rn_r; } ;
struct radix_mask {int rm_flags; int rm_b; scalar_t__ rm_mask; struct radix_node* rm_leaf; struct radix_mask* rm_mklist; } ;
typedef  int* caddr_t ;

/* Variables and functions */
 int RNF_NORMAL ; 
 int RNF_ROOT ; 
 int min (size_t,int) ; 
 scalar_t__ rn_satisfies_leaf (int*,struct radix_node*,int) ; 
 struct radix_node* rn_search_m (int*,struct radix_node*,scalar_t__) ; 

__attribute__((used)) static struct radix_node *
rn_match(void *v_arg,
	 struct radix_node_head *head)
{
	caddr_t v = v_arg;
	struct radix_node *t = head->rnh_treetop, *x;
	caddr_t cp = v, cp2;
	caddr_t cplim;
	struct radix_node *saved_t, *top = t;
	int off = t->rn_off, vlen = *(u_char *)cp, matched_off;
	int test, b, rn_b;

	/*
	 * Open code rn_search(v, top) to avoid overhead of extra
	 * subroutine call.
	 */
	for (; t->rn_b >= 0; ) {
		if (t->rn_bmask & cp[t->rn_off])
			t = t->rn_r;
		else
			t = t->rn_l;
	}
	/*
	 * See if we match exactly as a host destination
	 * or at least learn how many bits match, for normal mask finesse.
	 *
	 * It doesn't hurt us to limit how many bytes to check
	 * to the length of the mask, since if it matches we had a genuine
	 * match and the leaf we have is the most specific one anyway;
	 * if it didn't match with a shorter length it would fail
	 * with a long one.  This wins big for class B&C netmasks which
	 * are probably the most common case...
	 */
	if (t->rn_mask)
		vlen = *(u_char *)t->rn_mask;
	cp += off; cp2 = t->rn_key + off; cplim = v + vlen;
	for (; cp < cplim; cp++, cp2++)
		if (*cp != *cp2)
			goto on1;
	/*
	 * This extra grot is in case we are explicitly asked
	 * to look up the default.  Ugh!
	 * Or 255.255.255.255
	 *
	 * In this case, we have a complete match of the key.  Unless
	 * the node is one of the roots, we are finished.
	 * If it is the zeros root, then take what we have, preferring
	 * any real data.
	 * If it is the ones root, then pretend the target key was followed
	 * by a byte of zeros.
	 */
	if (!(t->rn_flags & RNF_ROOT))
		return t;		/* not a root */
	if (t->rn_dupedkey) {
		t = t->rn_dupedkey;
		return t;		/* have some real data */
	}
	if (*(cp-1) == 0)
		return t;		/* not the ones root */
	b = 0;				/* fake a zero after 255.255.255.255 */
	goto on2;
on1:
	test = (*cp ^ *cp2) & 0xff; /* find first bit that differs */
	for (b = 7; (test >>= 1) > 0;)
		b--;
on2:
	matched_off = cp - v;
	b += matched_off << 3;
	rn_b = -1 - b;
	/*
	 * If there is a host route in a duped-key chain, it will be first.
	 */
	if ((saved_t = t)->rn_mask == 0)
		t = t->rn_dupedkey;
	for (; t; t = t->rn_dupedkey) {
		/*
		 * Even if we don't match exactly as a host,
		 * we may match if the leaf we wound up at is
		 * a route to a net.
		 */
		if (t->rn_flags & RNF_NORMAL) {
			if (rn_b <= t->rn_b)
				return t;
		} else if (rn_satisfies_leaf(v, t, matched_off)) {
			return t;
		}
	}
	t = saved_t;
	/* start searching up the tree */
	do {
		struct radix_mask *m;
		t = t->rn_p;
		if ((m = t->rn_mklist)) {
			/*
			 * If non-contiguous masks ever become important
			 * we can restore the masking and open coding of
			 * the search and satisfaction test and put the
			 * calculation of "off" back before the "do".
			 */
			do {
				if (m->rm_flags & RNF_NORMAL) {
					if (rn_b <= m->rm_b)
						return (m->rm_leaf);
				} else {
					off = min(t->rn_off, matched_off);
					x = rn_search_m(v, t, m->rm_mask);
					while (x && x->rn_mask != m->rm_mask)
						x = x->rn_dupedkey;
					if (x && rn_satisfies_leaf(v, x, off))
						    return x;
				}
			} while ((m = m->rm_mklist));
		}
	} while (t != top);
	return 0;
}