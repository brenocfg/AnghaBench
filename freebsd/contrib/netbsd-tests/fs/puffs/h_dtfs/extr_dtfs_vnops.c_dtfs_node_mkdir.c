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
struct vattr {int dummy; } ;
struct puffs_usermount {int dummy; } ;
struct puffs_node {int /*<<< orphan*/  pn_va; } ;
struct puffs_newinfo {int dummy; } ;
struct puffs_cn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VDIR ; 
 struct puffs_node* dtfs_genfile (struct puffs_node*,struct puffs_cn const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  puffs_newinfo_setcookie (struct puffs_newinfo*,struct puffs_node*) ; 
 int /*<<< orphan*/  puffs_setvattr (int /*<<< orphan*/ *,struct vattr const*) ; 

int
dtfs_node_mkdir(struct puffs_usermount *pu, void *opc,
	struct puffs_newinfo *pni, const struct puffs_cn *pcn,
	const struct vattr *va)
{
	struct puffs_node *pn_parent = opc;
	struct puffs_node *pn_new;

	pn_new = dtfs_genfile(pn_parent, pcn, VDIR);
	puffs_setvattr(&pn_new->pn_va, va);

	puffs_newinfo_setcookie(pni, pn_new);

	return 0;
}