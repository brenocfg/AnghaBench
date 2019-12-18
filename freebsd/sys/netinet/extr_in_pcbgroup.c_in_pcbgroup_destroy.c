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
typedef  size_t u_int ;
struct inpcbinfo {scalar_t__ ipi_npcbgroups; scalar_t__ ipi_hashfields; struct inpcbgroup* ipi_pcbgroups; int /*<<< orphan*/  ipi_wildmask; int /*<<< orphan*/  ipi_wildbase; int /*<<< orphan*/  ipi_listhead; } ;
struct inpcbgroup {int /*<<< orphan*/  ipg_hashmask; int /*<<< orphan*/  ipg_hashbase; } ;

/* Variables and functions */
 int /*<<< orphan*/  CK_LIST_EMPTY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INP_GROUP_LOCK_DESTROY (struct inpcbgroup*) ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  M_PCB ; 
 int /*<<< orphan*/  free (struct inpcbgroup*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hashdestroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
in_pcbgroup_destroy(struct inpcbinfo *pcbinfo)
{
	struct inpcbgroup *pcbgroup;
	u_int pgn;

	if (pcbinfo->ipi_npcbgroups == 0)
		return;

	for (pgn = 0; pgn < pcbinfo->ipi_npcbgroups; pgn++) {
		pcbgroup = &pcbinfo->ipi_pcbgroups[pgn];
		KASSERT(CK_LIST_EMPTY(pcbinfo->ipi_listhead),
		    ("in_pcbinfo_destroy: listhead not empty"));
		INP_GROUP_LOCK_DESTROY(pcbgroup);
		hashdestroy(pcbgroup->ipg_hashbase, M_PCB,
		    pcbgroup->ipg_hashmask);
	}
	hashdestroy(pcbinfo->ipi_wildbase, M_PCB, pcbinfo->ipi_wildmask);
	free(pcbinfo->ipi_pcbgroups, M_PCB);
	pcbinfo->ipi_pcbgroups = NULL;
	pcbinfo->ipi_npcbgroups = 0;
	pcbinfo->ipi_hashfields = 0;
}