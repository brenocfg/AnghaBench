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
struct pf_fragment {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (struct pf_fragment*,char*) ; 
 int /*<<< orphan*/  PF_FRAG_ASSERT () ; 
 int /*<<< orphan*/  RB_REMOVE (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct pf_fragment*) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct pf_fragment*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V_pf_frag_tree ; 
 int /*<<< orphan*/  V_pf_frag_z ; 
 int /*<<< orphan*/  V_pf_fragqueue ; 
 int /*<<< orphan*/  frag_next ; 
 int /*<<< orphan*/  pf_frag_tree ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,struct pf_fragment*) ; 

__attribute__((used)) static void
pf_remove_fragment(struct pf_fragment *frag)
{

	PF_FRAG_ASSERT();
	KASSERT(frag, ("frag != NULL"));

	RB_REMOVE(pf_frag_tree, &V_pf_frag_tree, frag);
	TAILQ_REMOVE(&V_pf_fragqueue, frag, frag_next);
	uma_zfree(V_pf_frag_z, frag);
}