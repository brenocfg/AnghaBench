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
struct TYPE_2__ {int /*<<< orphan*/  va_gid; int /*<<< orphan*/  va_uid; int /*<<< orphan*/  va_mode; int /*<<< orphan*/  va_type; } ;
struct puffs_node {TYPE_1__ pn_va; } ;
struct puffs_cred {int dummy; } ;

/* Variables and functions */
 int puffs_access (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct puffs_cred const*) ; 

int
dtfs_node_access(struct puffs_usermount *pu, void *opc, int acc_mode,
	const struct puffs_cred *pcr)
{
	struct puffs_node *pn = opc;

	return puffs_access(pn->pn_va.va_type, pn->pn_va.va_mode,
	    pn->pn_va.va_uid, pn->pn_va.va_gid, acc_mode, pcr);
}