#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct puffs_usermount {int dummy; } ;
struct TYPE_2__ {scalar_t__ va_nlink; } ;
struct puffs_node {TYPE_1__ pn_va; } ;

/* Variables and functions */
 int /*<<< orphan*/  dtfs_freenode (struct puffs_node*) ; 

int
dtfs_node_reclaim(struct puffs_usermount *pu, void *opc)
{
	struct puffs_node *pn = opc;

	if (pn->pn_va.va_nlink == 0)
		dtfs_freenode(pn);

	return 0;
}