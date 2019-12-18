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
struct pf_frent {int /*<<< orphan*/  fe_m; } ;
struct pf_fragment {int /*<<< orphan*/  fr_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  PF_FRAG_ASSERT () ; 
 struct pf_frent* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct pf_frent*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V_pf_frent_z ; 
 int /*<<< orphan*/  fr_next ; 
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pf_remove_fragment (struct pf_fragment*) ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,struct pf_frent*) ; 

__attribute__((used)) static void
pf_free_fragment(struct pf_fragment *frag)
{
	struct pf_frent		*frent;

	PF_FRAG_ASSERT();

	/* Free all fragments */
	for (frent = TAILQ_FIRST(&frag->fr_queue); frent;
	    frent = TAILQ_FIRST(&frag->fr_queue)) {
		TAILQ_REMOVE(&frag->fr_queue, frent, fr_next);

		m_freem(frent->fe_m);
		uma_zfree(V_pf_frent_z, frent);
	}

	pf_remove_fragment(frag);
}