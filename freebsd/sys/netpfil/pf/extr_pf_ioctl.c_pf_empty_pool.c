#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * tbl; int /*<<< orphan*/  dyn; } ;
struct TYPE_4__ {int type; TYPE_1__ p; } ;
struct pf_pooladdr {scalar_t__ kif; TYPE_2__ addr; } ;
struct pf_palist {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_PFRULE ; 
#define  PF_ADDR_DYNIFTL 129 
#define  PF_ADDR_TABLE 128 
 struct pf_pooladdr* TAILQ_FIRST (struct pf_palist*) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (struct pf_palist*,struct pf_pooladdr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  entries ; 
 int /*<<< orphan*/  free (struct pf_pooladdr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfi_dynaddr_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfi_kif_unref (scalar_t__) ; 
 int /*<<< orphan*/  pfr_detach_table (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
pf_empty_pool(struct pf_palist *poola)
{
	struct pf_pooladdr *pa;

	while ((pa = TAILQ_FIRST(poola)) != NULL) {
		switch (pa->addr.type) {
		case PF_ADDR_DYNIFTL:
			pfi_dynaddr_remove(pa->addr.p.dyn);
			break;
		case PF_ADDR_TABLE:
			/* XXX: this could be unfinished pooladdr on pabuf */
			if (pa->addr.p.tbl != NULL)
				pfr_detach_table(pa->addr.p.tbl);
			break;
		}
		if (pa->kif)
			pfi_kif_unref(pa->kif);
		TAILQ_REMOVE(poola, pa, entries);
		free(pa, M_PFRULE);
	}
}