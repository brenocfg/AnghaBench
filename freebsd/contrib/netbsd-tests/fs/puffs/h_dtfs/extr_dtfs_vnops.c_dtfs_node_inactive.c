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
typedef  struct puffs_node* puffs_cookie_t ;

/* Variables and functions */
 int /*<<< orphan*/  PUFFS_SETBACK_NOREF_N1 ; 
 int /*<<< orphan*/  puffs_cc_getcc (struct puffs_usermount*) ; 
 int /*<<< orphan*/  puffs_setback (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
dtfs_node_inactive(struct puffs_usermount *pu, puffs_cookie_t opc)
{
	struct puffs_node *pn = opc;

	if (pn->pn_va.va_nlink == 0)
		puffs_setback(puffs_cc_getcc(pu), PUFFS_SETBACK_NOREF_N1);
	return 0;
}