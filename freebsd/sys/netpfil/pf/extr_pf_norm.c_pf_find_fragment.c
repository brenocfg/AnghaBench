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
struct pf_fragment_cmp {int dummy; } ;
struct pf_fragment {int /*<<< orphan*/  fr_timeout; } ;
struct pf_frag_tree {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PF_FRAG_ASSERT () ; 
 struct pf_fragment* RB_FIND (int /*<<< orphan*/ ,struct pf_frag_tree*,struct pf_fragment*) ; 
 int /*<<< orphan*/  TAILQ_INSERT_HEAD (int /*<<< orphan*/ *,struct pf_fragment*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct pf_fragment*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V_pf_fragqueue ; 
 int /*<<< orphan*/  frag_next ; 
 int /*<<< orphan*/  pf_frag_tree ; 
 int /*<<< orphan*/  time_uptime ; 

__attribute__((used)) static struct pf_fragment *
pf_find_fragment(struct pf_fragment_cmp *key, struct pf_frag_tree *tree)
{
	struct pf_fragment	*frag;

	PF_FRAG_ASSERT();

	frag = RB_FIND(pf_frag_tree, tree, (struct pf_fragment *)key);
	if (frag != NULL) {
		/* XXX Are we sure we want to update the timeout? */
		frag->fr_timeout = time_uptime;
		TAILQ_REMOVE(&V_pf_fragqueue, frag, frag_next);
		TAILQ_INSERT_HEAD(&V_pf_fragqueue, frag, frag_next);
	}

	return (frag);
}