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
struct mibif {int /*<<< orphan*/  name; } ;
struct bridge_if {int /*<<< orphan*/  num_addrs; int /*<<< orphan*/  bif_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  bridge_addrs_update_listage () ; 
 struct bridge_if* bridge_first_bif () ; 
 struct bridge_if* bridge_next_bif (struct bridge_if*) ; 
 int /*<<< orphan*/  bridge_remove_bif (struct bridge_if*) ; 
 int /*<<< orphan*/  bridge_update_addrs (struct bridge_if*) ; 
 struct mibif* mib_first_if () ; 
 struct mibif* mib_next_if (struct mibif*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
bridge_update_all_addrs(void)
{
	struct mibif *ifp;
	struct bridge_if *bif, *t_bif;

	for (bif = bridge_first_bif(); bif != NULL; bif = t_bif) {
		t_bif = bridge_next_bif(bif);

		for (ifp = mib_first_if(); ifp != NULL;
		    ifp = mib_next_if(ifp))
			if (strcmp(ifp->name, bif->bif_name) == 0)
				break;

		if (ifp != NULL)
			bif->num_addrs = bridge_update_addrs(bif);
		else  /* Ops, we don't exist anymore. */
			bridge_remove_bif(bif);
	}

	bridge_addrs_update_listage();
}