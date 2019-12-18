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
struct pfi_kif {struct ifg_group* pfik_group; } ;
struct ifg_group {struct pfi_kif* ifg_pf_kif; int /*<<< orphan*/  ifg_group; } ;

/* Variables and functions */
 int /*<<< orphan*/  PF_RULES_WASSERT () ; 
 int /*<<< orphan*/  V_pfi_update ; 
 struct pfi_kif* pfi_kif_attach (struct pfi_kif*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pfi_attach_ifgroup(struct ifg_group *ifg, struct pfi_kif *kif)
{

	PF_RULES_WASSERT();

	V_pfi_update++;
	kif = pfi_kif_attach(kif, ifg->ifg_group);
	kif->pfik_group = ifg;
	ifg->ifg_pf_kif = kif;
}