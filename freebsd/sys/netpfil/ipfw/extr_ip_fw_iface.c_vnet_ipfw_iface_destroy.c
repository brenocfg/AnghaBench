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
struct namedobj_instance {int dummy; } ;
struct ip_fw_chain {int /*<<< orphan*/ * ifcfg; } ;

/* Variables and functions */
 struct namedobj_instance* CHAIN_TO_II (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  IPFW_UH_WLOCK (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  IPFW_UH_WUNLOCK (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  destroy_iface ; 
 int /*<<< orphan*/  iface_khandler_deregister () ; 
 int /*<<< orphan*/  ipfw_objhash_destroy (struct namedobj_instance*) ; 
 int /*<<< orphan*/  ipfw_objhash_foreach (struct namedobj_instance*,int /*<<< orphan*/ ,struct ip_fw_chain*) ; 

void
vnet_ipfw_iface_destroy(struct ip_fw_chain *ch)
{
	struct namedobj_instance *ii;

	IPFW_UH_WLOCK(ch);
	ii = CHAIN_TO_II(ch);
	ch->ifcfg = NULL;
	IPFW_UH_WUNLOCK(ch);

	if (ii != NULL) {
		ipfw_objhash_foreach(ii, destroy_iface, ch);
		ipfw_objhash_destroy(ii);
		iface_khandler_deregister();
	}
}