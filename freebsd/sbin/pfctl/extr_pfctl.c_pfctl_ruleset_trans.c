#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pfctl {int loadopt; TYPE_1__* trans; int /*<<< orphan*/  dev; struct pf_anchor** astack; } ;
struct pf_anchor {int dummy; } ;
struct TYPE_3__ {int pfrb_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIOCXBEGIN ; 
 int PFCTL_FLAG_ALTQ ; 
 int PFCTL_FLAG_FILTER ; 
 int PFCTL_FLAG_NAT ; 
 int PFCTL_FLAG_TABLE ; 
 int /*<<< orphan*/  PF_RULESET_ALTQ ; 
 int /*<<< orphan*/  PF_RULESET_BINAT ; 
 int /*<<< orphan*/  PF_RULESET_FILTER ; 
 int /*<<< orphan*/  PF_RULESET_NAT ; 
 int /*<<< orphan*/  PF_RULESET_RDR ; 
 int /*<<< orphan*/  PF_RULESET_SCRUB ; 
 int /*<<< orphan*/  PF_RULESET_TABLE ; 
 scalar_t__ altqsupport ; 
 scalar_t__ pfctl_add_trans (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ pfctl_trans (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int) ; 

int
pfctl_ruleset_trans(struct pfctl *pf, char *path, struct pf_anchor *a)
{
	int osize = pf->trans->pfrb_size;

	if ((pf->loadopt & PFCTL_FLAG_NAT) != 0) {
		if (pfctl_add_trans(pf->trans, PF_RULESET_NAT, path) ||
		    pfctl_add_trans(pf->trans, PF_RULESET_BINAT, path) ||
		    pfctl_add_trans(pf->trans, PF_RULESET_RDR, path))
			return (1);
	}
	if (a == pf->astack[0] && ((altqsupport &&
	    (pf->loadopt & PFCTL_FLAG_ALTQ) != 0))) {
		if (pfctl_add_trans(pf->trans, PF_RULESET_ALTQ, path))
			return (2);
	}
	if ((pf->loadopt & PFCTL_FLAG_FILTER) != 0) {
		if (pfctl_add_trans(pf->trans, PF_RULESET_SCRUB, path) ||
		    pfctl_add_trans(pf->trans, PF_RULESET_FILTER, path))
			return (3);
	}
	if (pf->loadopt & PFCTL_FLAG_TABLE)
		if (pfctl_add_trans(pf->trans, PF_RULESET_TABLE, path))
			return (4);
	if (pfctl_trans(pf->dev, pf->trans, DIOCXBEGIN, osize))
		return (5);

	return (0);
}