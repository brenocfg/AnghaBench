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
struct pfi_kif {TYPE_2__* pfik_ifp; TYPE_1__* pfik_group; } ;
struct TYPE_4__ {int /*<<< orphan*/ * if_pf_kif; } ;
struct TYPE_3__ {int /*<<< orphan*/ * ifg_pf_kif; } ;

/* Variables and functions */
 struct pfi_kif* LIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct pfi_kif*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PFI_MTYPE ; 
 int /*<<< orphan*/  PF_RULES_WASSERT () ; 
 struct pfi_kif* RB_MIN (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RB_REMOVE (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct pfi_kif*) ; 
 int /*<<< orphan*/ * V_pfi_all ; 
 struct pfi_kif* V_pfi_buffer ; 
 int /*<<< orphan*/  V_pfi_ifs ; 
 int /*<<< orphan*/  V_pfi_unlinked_kifs ; 
 int /*<<< orphan*/  free (struct pfi_kif*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_rele (TYPE_2__*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pfi_ifhead ; 
 int /*<<< orphan*/  pfi_unlnkdkifs_mtx ; 
 int /*<<< orphan*/  pfik_list ; 

void
pfi_cleanup_vnet(void)
{
	struct pfi_kif *kif;

	PF_RULES_WASSERT();

	V_pfi_all = NULL;
	while ((kif = RB_MIN(pfi_ifhead, &V_pfi_ifs))) {
		RB_REMOVE(pfi_ifhead, &V_pfi_ifs, kif);
		if (kif->pfik_group)
			kif->pfik_group->ifg_pf_kif = NULL;
		if (kif->pfik_ifp) {
			if_rele(kif->pfik_ifp);
			kif->pfik_ifp->if_pf_kif = NULL;
		}
		free(kif, PFI_MTYPE);
	}

	mtx_lock(&pfi_unlnkdkifs_mtx);
	while ((kif = LIST_FIRST(&V_pfi_unlinked_kifs))) {
		LIST_REMOVE(kif, pfik_list);
		free(kif, PFI_MTYPE);
	}
	mtx_unlock(&pfi_unlnkdkifs_mtx);

	free(V_pfi_buffer, PFI_MTYPE);
}