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
struct pfi_kif {struct ifnet* pfik_ifp; } ;
struct ifnet {struct pfi_kif* if_pf_kif; int /*<<< orphan*/  if_xname; } ;

/* Variables and functions */
 int /*<<< orphan*/  PF_RULES_WASSERT () ; 
 int /*<<< orphan*/  V_pfi_update ; 
 int /*<<< orphan*/  if_ref (struct ifnet*) ; 
 struct pfi_kif* pfi_kif_attach (struct pfi_kif*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfi_kif_update (struct pfi_kif*) ; 

__attribute__((used)) static void
pfi_attach_ifnet(struct ifnet *ifp, struct pfi_kif *kif)
{

	PF_RULES_WASSERT();

	V_pfi_update++;
	kif = pfi_kif_attach(kif, ifp->if_xname);
	if_ref(ifp);
	kif->pfik_ifp = ifp;
	ifp->if_pf_kif = kif;
	pfi_kif_update(kif);
}