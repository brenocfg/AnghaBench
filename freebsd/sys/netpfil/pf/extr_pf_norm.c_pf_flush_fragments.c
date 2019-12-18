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
 int /*<<< orphan*/  DPFPRINTF (char*) ; 
 int /*<<< orphan*/  PF_FRAG_ASSERT () ; 
 struct pf_fragment* TAILQ_LAST (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V_pf_fragqueue ; 
 int /*<<< orphan*/  V_pf_frent_z ; 
 int /*<<< orphan*/  pf_fragqueue ; 
 int /*<<< orphan*/  pf_free_fragment (struct pf_fragment*) ; 
 int uma_zone_get_cur (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pf_flush_fragments(void)
{
	struct pf_fragment	*frag;
	int			 goal;

	PF_FRAG_ASSERT();

	goal = uma_zone_get_cur(V_pf_frent_z) * 9 / 10;
	DPFPRINTF(("trying to free %d frag entriess\n", goal));
	while (goal < uma_zone_get_cur(V_pf_frent_z)) {
		frag = TAILQ_LAST(&V_pf_fragqueue, pf_fragqueue);
		if (frag)
			pf_free_fragment(frag);
		else
			break;
	}
}