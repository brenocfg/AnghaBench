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
struct radix_node {short rn_bit; scalar_t__ rn_key; scalar_t__ rn_mask; int rn_flags; scalar_t__ rn_mklist; struct radix_node* rn_parent; struct radix_node* rn_dupedkey; struct radix_node* rn_right; struct radix_node* rn_left; struct radix_node* rn_ybro; struct radix_node* rn_twin; scalar_t__ rn_info; int /*<<< orphan*/  rn_offset; } ;
struct radix_mask {short rm_bit; int rm_flags; scalar_t__ rm_mask; int /*<<< orphan*/  rm_refs; TYPE_1__* rm_leaf; struct radix_mask* rm_mklist; } ;
struct radix_head {int /*<<< orphan*/  rnh_masks; struct radix_node* rnh_treetop; } ;
typedef  scalar_t__ caddr_t ;
struct TYPE_2__ {scalar_t__ rn_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERR ; 
 int RNF_ACTIVE ; 
 int RNF_NORMAL ; 
 int /*<<< orphan*/  log (int /*<<< orphan*/ ,char*) ; 
 struct radix_node* rn_addmask (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct radix_node* rn_clist ; 
 struct radix_node* rn_insert (scalar_t__,struct radix_head*,int*,struct radix_node*) ; 
 scalar_t__ rn_lexobetter (scalar_t__,scalar_t__) ; 
 scalar_t__ rn_mpath_capable (struct radix_head*) ; 
 struct radix_mask* rn_new_radix_mask (struct radix_node*,struct radix_mask*) ; 
 int /*<<< orphan*/  rn_nodenum ; 
 scalar_t__ rn_refines (scalar_t__,scalar_t__) ; 

struct radix_node *
rn_addroute(void *v_arg, void *n_arg, struct radix_head *head,
    struct radix_node treenodes[2])
{
	caddr_t v = (caddr_t)v_arg, netmask = (caddr_t)n_arg;
	struct radix_node *t, *x = NULL, *tt;
	struct radix_node *saved_tt, *top = head->rnh_treetop;
	short b = 0, b_leaf = 0;
	int keyduplicated;
	caddr_t mmask;
	struct radix_mask *m, **mp;

	/*
	 * In dealing with non-contiguous masks, there may be
	 * many different routes which have the same mask.
	 * We will find it useful to have a unique pointer to
	 * the mask to speed avoiding duplicate references at
	 * nodes and possibly save time in calculating indices.
	 */
	if (netmask)  {
		x = rn_addmask(netmask, head->rnh_masks, 0, top->rn_offset);
		if (x == NULL)
			return (0);
		b_leaf = x->rn_bit;
		b = -1 - x->rn_bit;
		netmask = x->rn_key;
	}
	/*
	 * Deal with duplicated keys: attach node to previous instance
	 */
	saved_tt = tt = rn_insert(v, head, &keyduplicated, treenodes);
	if (keyduplicated) {
		for (t = tt; tt; t = tt, tt = tt->rn_dupedkey) {
#ifdef RADIX_MPATH
			/* permit multipath, if enabled for the family */
			if (rn_mpath_capable(head) && netmask == tt->rn_mask) {
				/*
				 * go down to the end of multipaths, so that
				 * new entry goes into the end of rn_dupedkey
				 * chain.
				 */
				do {
					t = tt;
					tt = tt->rn_dupedkey;
				} while (tt && t->rn_mask == tt->rn_mask);
				break;
			}
#endif
			if (tt->rn_mask == netmask)
				return (0);
			if (netmask == 0 ||
			    (tt->rn_mask &&
			     ((b_leaf < tt->rn_bit) /* index(netmask) > node */
			      || rn_refines(netmask, tt->rn_mask)
			      || rn_lexobetter(netmask, tt->rn_mask))))
				break;
		}
		/*
		 * If the mask is not duplicated, we wouldn't
		 * find it among possible duplicate key entries
		 * anyway, so the above test doesn't hurt.
		 *
		 * We sort the masks for a duplicated key the same way as
		 * in a masklist -- most specific to least specific.
		 * This may require the unfortunate nuisance of relocating
		 * the head of the list.
		 *
		 * We also reverse, or doubly link the list through the
		 * parent pointer.
		 */
		if (tt == saved_tt) {
			struct	radix_node *xx = x;
			/* link in at head of list */
			(tt = treenodes)->rn_dupedkey = t;
			tt->rn_flags = t->rn_flags;
			tt->rn_parent = x = t->rn_parent;
			t->rn_parent = tt;	 		/* parent */
			if (x->rn_left == t)
				x->rn_left = tt;
			else
				x->rn_right = tt;
			saved_tt = tt; x = xx;
		} else {
			(tt = treenodes)->rn_dupedkey = t->rn_dupedkey;
			t->rn_dupedkey = tt;
			tt->rn_parent = t;			/* parent */
			if (tt->rn_dupedkey)			/* parent */
				tt->rn_dupedkey->rn_parent = tt; /* parent */
		}
#ifdef RN_DEBUG
		t=tt+1; tt->rn_info = rn_nodenum++; t->rn_info = rn_nodenum++;
		tt->rn_twin = t; tt->rn_ybro = rn_clist; rn_clist = tt;
#endif
		tt->rn_key = (caddr_t) v;
		tt->rn_bit = -1;
		tt->rn_flags = RNF_ACTIVE;
	}
	/*
	 * Put mask in tree.
	 */
	if (netmask) {
		tt->rn_mask = netmask;
		tt->rn_bit = x->rn_bit;
		tt->rn_flags |= x->rn_flags & RNF_NORMAL;
	}
	t = saved_tt->rn_parent;
	if (keyduplicated)
		goto on2;
	b_leaf = -1 - t->rn_bit;
	if (t->rn_right == saved_tt)
		x = t->rn_left;
	else
		x = t->rn_right;
	/* Promote general routes from below */
	if (x->rn_bit < 0) {
	    for (mp = &t->rn_mklist; x; x = x->rn_dupedkey)
		if (x->rn_mask && (x->rn_bit >= b_leaf) && x->rn_mklist == 0) {
			*mp = m = rn_new_radix_mask(x, 0);
			if (m)
				mp = &m->rm_mklist;
		}
	} else if (x->rn_mklist) {
		/*
		 * Skip over masks whose index is > that of new node
		 */
		for (mp = &x->rn_mklist; (m = *mp); mp = &m->rm_mklist)
			if (m->rm_bit >= b_leaf)
				break;
		t->rn_mklist = m; *mp = NULL;
	}
on2:
	/* Add new route to highest possible ancestor's list */
	if ((netmask == 0) || (b > t->rn_bit ))
		return (tt); /* can't lift at all */
	b_leaf = tt->rn_bit;
	do {
		x = t;
		t = t->rn_parent;
	} while (b <= t->rn_bit && x != top);
	/*
	 * Search through routes associated with node to
	 * insert new route according to index.
	 * Need same criteria as when sorting dupedkeys to avoid
	 * double loop on deletion.
	 */
	for (mp = &x->rn_mklist; (m = *mp); mp = &m->rm_mklist) {
		if (m->rm_bit < b_leaf)
			continue;
		if (m->rm_bit > b_leaf)
			break;
		if (m->rm_flags & RNF_NORMAL) {
			mmask = m->rm_leaf->rn_mask;
			if (tt->rn_flags & RNF_NORMAL) {
#if !defined(RADIX_MPATH)
			    log(LOG_ERR,
			        "Non-unique normal route, mask not entered\n");
#endif
				return (tt);
			}
		} else
			mmask = m->rm_mask;
		if (mmask == netmask) {
			m->rm_refs++;
			tt->rn_mklist = m;
			return (tt);
		}
		if (rn_refines(netmask, mmask)
		    || rn_lexobetter(netmask, mmask))
			break;
	}
	*mp = rn_new_radix_mask(tt, *mp);
	return (tt);
}