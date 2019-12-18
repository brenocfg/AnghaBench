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
struct TYPE_4__ {int ifmd_flags; } ;
struct mibif {TYPE_2__ mib; int /*<<< orphan*/ * physaddr; int /*<<< orphan*/  name; } ;
struct TYPE_3__ {int /*<<< orphan*/  octet; } ;
struct bridge_if {int /*<<< orphan*/  entry_age; int /*<<< orphan*/  num_ports; int /*<<< orphan*/  if_status; TYPE_1__ br_addr; int /*<<< orphan*/  bif_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETHER_ADDR_LEN ; 
 int IFF_RUNNING ; 
 int /*<<< orphan*/  RowStatus_active ; 
 int /*<<< orphan*/  RowStatus_notInService ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bridge_get_basemac (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int bridge_getinfo_bif (struct bridge_if*) ; 
 int /*<<< orphan*/  bridge_new_root (struct bridge_if*) ; 
 int /*<<< orphan*/  bridge_remove_bif (struct bridge_if*) ; 
 int /*<<< orphan*/  bridge_top_change (struct bridge_if*) ; 
 int /*<<< orphan*/  bridge_update_memif (struct bridge_if*) ; 
 struct mibif* mib_first_if () ; 
 struct mibif* mib_next_if (struct mibif*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
bridge_update_bif(struct bridge_if *bif)
{
	struct mibif *ifp;

	/* Walk through the mibII interface list. */
	for (ifp = mib_first_if(); ifp != NULL; ifp = mib_next_if(ifp))
		if (strcmp(ifp->name, bif->bif_name) == 0)
			break;

	if (ifp == NULL) {
		/* Ops, we do not exist anymore. */
		bridge_remove_bif(bif);
		return (0);
	}

	if (ifp->physaddr != NULL )
		bcopy(ifp->physaddr, bif->br_addr.octet, ETHER_ADDR_LEN);
	else
		bridge_get_basemac(bif->bif_name, bif->br_addr.octet,
		    ETHER_ADDR_LEN);

	if (ifp->mib.ifmd_flags & IFF_RUNNING)
		bif->if_status = RowStatus_active;
	else
		bif->if_status = RowStatus_notInService;

	switch (bridge_getinfo_bif(bif)) {
		case 2:
			bridge_new_root(bif);
			break;
		case 1:
			bridge_top_change(bif);
			break;
		case -1:
			bridge_remove_bif(bif);
			return (-1);
		default:
			break;
	}

	/*
	 * The number of ports is accessible via SNMP -
	 * update the ports each time the bridge interface data
	 * is refreshed too.
	 */
	bif->num_ports = bridge_update_memif(bif);
	bif->entry_age = time(NULL);

	return (1);
}