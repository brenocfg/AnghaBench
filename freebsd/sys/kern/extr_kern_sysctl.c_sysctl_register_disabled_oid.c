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
struct sysctl_oid {int oid_kind; } ;

/* Variables and functions */
 int CTLFLAG_DORMANT ; 
 int CTLTYPE ; 
 int CTLTYPE_NODE ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  sysctl_register_oid (struct sysctl_oid*) ; 

void
sysctl_register_disabled_oid(struct sysctl_oid *oidp)
{

	/*
	 * Mark the leaf as dormant if it's not to be immediately enabled.
	 * We do not disable nodes as they can be shared between modules
	 * and it is always safe to access a node.
	 */
	KASSERT((oidp->oid_kind & CTLFLAG_DORMANT) == 0,
	    ("internal flag is set in oid_kind"));
	if ((oidp->oid_kind & CTLTYPE) != CTLTYPE_NODE)
		oidp->oid_kind |= CTLFLAG_DORMANT;
	sysctl_register_oid(oidp);
}