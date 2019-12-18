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
struct ipfw_iface {int dummy; } ;
struct ip_fw_chain {int dummy; } ;
struct ifnet {int /*<<< orphan*/  if_index; } ;

/* Variables and functions */
 struct namedobj_instance* CHAIN_TO_II (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  IPFW_UH_WLOCK (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  IPFW_UH_WUNLOCK (struct ip_fw_chain*) ; 
 scalar_t__ V_ipfw_vnet_ready ; 
 struct ip_fw_chain V_layer3_chain ; 
 int /*<<< orphan*/  handle_ifattach (struct ip_fw_chain*,struct ipfw_iface*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_ifdetach (struct ip_fw_chain*,struct ipfw_iface*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_name (struct ifnet*) ; 
 scalar_t__ ipfw_objhash_lookup_name (struct namedobj_instance*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ipfw_kifhandler(void *arg, struct ifnet *ifp)
{
	struct ip_fw_chain *ch;
	struct ipfw_iface *iif;
	struct namedobj_instance *ii;
	uintptr_t htype;

	if (V_ipfw_vnet_ready == 0)
		return;

	ch = &V_layer3_chain;
	htype = (uintptr_t)arg;

	IPFW_UH_WLOCK(ch);
	ii = CHAIN_TO_II(ch);
	if (ii == NULL) {
		IPFW_UH_WUNLOCK(ch);
		return;
	}
	iif = (struct ipfw_iface*)ipfw_objhash_lookup_name(ii, 0,
	    if_name(ifp));
	if (iif != NULL) {
		if (htype == 1)
			handle_ifattach(ch, iif, ifp->if_index);
		else
			handle_ifdetach(ch, iif, ifp->if_index);
	}
	IPFW_UH_WUNLOCK(ch);
}