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
struct ip_fw_chain {struct namedobj_instance* ifcfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_IFACES ; 
 int /*<<< orphan*/  IPFW_UH_WLOCK (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  IPFW_UH_WUNLOCK (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  iface_khandler_register () ; 
 struct namedobj_instance* ipfw_objhash_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipfw_objhash_destroy (struct namedobj_instance*) ; 

__attribute__((used)) static void
vnet_ipfw_iface_init(struct ip_fw_chain *ch)
{
	struct namedobj_instance *ii;

	ii = ipfw_objhash_create(DEFAULT_IFACES);
	IPFW_UH_WLOCK(ch);
	if (ch->ifcfg == NULL) {
		ch->ifcfg = ii;
		ii = NULL;
	}
	IPFW_UH_WUNLOCK(ch);

	if (ii != NULL) {
		/* Already initialized. Free namehash. */
		ipfw_objhash_destroy(ii);
	} else {
		/* We're the first ones. Init kernel hooks. */
		iface_khandler_register();
	}
}