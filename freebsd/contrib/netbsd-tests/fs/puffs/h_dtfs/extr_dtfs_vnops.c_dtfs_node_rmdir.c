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
struct puffs_usermount {int dummy; } ;
struct puffs_node {int dummy; } ;
struct puffs_cn {int /*<<< orphan*/  pcn_namelen; int /*<<< orphan*/  pcn_name; } ;
struct dtfs_file {int /*<<< orphan*/  df_dirents; } ;

/* Variables and functions */
 struct dtfs_file* DTFS_CTOF (void*) ; 
 int ENOTEMPTY ; 
 int /*<<< orphan*/  LIST_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PUFFS_SETBACK_NOREF_N2 ; 
 int /*<<< orphan*/  dtfs_nukenode (void*,struct puffs_node*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  puffs_cc_getcc (struct puffs_usermount*) ; 
 int /*<<< orphan*/  puffs_setback (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
dtfs_node_rmdir(struct puffs_usermount *pu, void *opc, void *targ,
	const struct puffs_cn *pcn)
{
	struct puffs_node *pn_parent = opc;
	struct dtfs_file *df = DTFS_CTOF(targ);

	if (!LIST_EMPTY(&df->df_dirents))
		return ENOTEMPTY;

	dtfs_nukenode(targ, pn_parent, pcn->pcn_name, pcn->pcn_namelen);
	puffs_setback(puffs_cc_getcc(pu), PUFFS_SETBACK_NOREF_N2);

	return 0;
}