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
struct namedobj_instance {int dummy; } ;
struct ipfw_ifc {struct ipfw_iface* iface; } ;
struct TYPE_2__ {int refcnt; int /*<<< orphan*/  name; } ;
struct ipfw_iface {scalar_t__ ifindex; int resolved; TYPE_1__ no; int /*<<< orphan*/  ifname; int /*<<< orphan*/  consumers; } ;
struct ip_fw_chain {int dummy; } ;

/* Variables and functions */
 struct namedobj_instance* CHAIN_TO_II (struct ip_fw_chain*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  IPFW_UH_WLOCK (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  IPFW_UH_WUNLOCK (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  M_IPFW ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct ipfw_iface*,int /*<<< orphan*/ ) ; 
 scalar_t__ ipfw_kiflookup (char*) ; 
 int /*<<< orphan*/  ipfw_objhash_add (struct namedobj_instance*,TYPE_1__*) ; 
 scalar_t__ ipfw_objhash_lookup_name (struct namedobj_instance*,int /*<<< orphan*/ ,char*) ; 
 struct ipfw_iface* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  vnet_ipfw_iface_init (struct ip_fw_chain*) ; 

int
ipfw_iface_ref(struct ip_fw_chain *ch, char *name,
    struct ipfw_ifc *ic)
{
	struct namedobj_instance *ii;
	struct ipfw_iface *iif, *tmp;

	if (strlen(name) >= sizeof(iif->ifname))
		return (EINVAL);

	IPFW_UH_WLOCK(ch);

	ii = CHAIN_TO_II(ch);
	if (ii == NULL) {

		/*
		 * First request to subsystem.
		 * Let's perform init.
		 */
		IPFW_UH_WUNLOCK(ch);
		vnet_ipfw_iface_init(ch);
		IPFW_UH_WLOCK(ch);
		ii = CHAIN_TO_II(ch);
	}

	iif = (struct ipfw_iface *)ipfw_objhash_lookup_name(ii, 0, name);

	if (iif != NULL) {
		iif->no.refcnt++;
		ic->iface = iif;
		IPFW_UH_WUNLOCK(ch);
		return (0);
	}

	IPFW_UH_WUNLOCK(ch);

	/* Not found. Let's create one */
	iif = malloc(sizeof(struct ipfw_iface), M_IPFW, M_WAITOK | M_ZERO);
	TAILQ_INIT(&iif->consumers);
	iif->no.name = iif->ifname;
	strlcpy(iif->ifname, name, sizeof(iif->ifname));

	/*
	 * Ref & link to the list.
	 *
	 * We assume  ifnet_arrival_event / ifnet_departure_event
	 * are not holding any locks.
	 */
	iif->no.refcnt = 1;
	IPFW_UH_WLOCK(ch);

	tmp = (struct ipfw_iface *)ipfw_objhash_lookup_name(ii, 0, name);
	if (tmp != NULL) {
		/* Interface has been created since unlock. Ref and return */
		tmp->no.refcnt++;
		ic->iface = tmp;
		IPFW_UH_WUNLOCK(ch);
		free(iif, M_IPFW);
		return (0);
	}

	iif->ifindex = ipfw_kiflookup(name);
	if (iif->ifindex != 0)
		iif->resolved = 1;

	ipfw_objhash_add(ii, &iif->no);
	ic->iface = iif;

	IPFW_UH_WUNLOCK(ch);

	return (0);
}