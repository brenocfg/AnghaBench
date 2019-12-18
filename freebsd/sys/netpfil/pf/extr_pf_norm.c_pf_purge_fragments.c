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
typedef  scalar_t__ uint32_t ;
struct pf_fragment {scalar_t__ fr_timeout; int /*<<< orphan*/  fr_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPFPRINTF (char*) ; 
 int /*<<< orphan*/  PF_FRAG_LOCK () ; 
 int /*<<< orphan*/  PF_FRAG_UNLOCK () ; 
 struct pf_fragment* TAILQ_LAST (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V_pf_fragqueue ; 
 int /*<<< orphan*/  pf_fragqueue ; 
 int /*<<< orphan*/  pf_free_fragment (struct pf_fragment*) ; 

void
pf_purge_fragments(uint32_t expire)
{
	struct pf_fragment	*frag;

	PF_FRAG_LOCK();
	while ((frag = TAILQ_LAST(&V_pf_fragqueue, pf_fragqueue)) != NULL) {
		if (frag->fr_timeout > expire)
			break;

		DPFPRINTF(("expiring %d(%p)\n", frag->fr_id, frag));
		pf_free_fragment(frag);
	}

	PF_FRAG_UNLOCK();
}