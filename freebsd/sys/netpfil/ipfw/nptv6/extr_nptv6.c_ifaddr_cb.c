#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nptv6_cfg {int flags; int /*<<< orphan*/  mask; int /*<<< orphan*/  internal; int /*<<< orphan*/  external; int /*<<< orphan*/  if_name; } ;
struct namedobj_instance {int dummy; } ;
struct named_object {int /*<<< orphan*/  kidx; } ;
struct ip_fw_chain {int dummy; } ;
struct ifaddr_event_args {scalar_t__ event; TYPE_1__* ifp; int /*<<< orphan*/ * addr; } ;
struct TYPE_3__ {int if_flags; int /*<<< orphan*/  if_xname; } ;

/* Variables and functions */
 scalar_t__ IFADDR_EVENT_DEL ; 
 int IFF_DYING ; 
 int /*<<< orphan*/  IF_NAMESIZE ; 
 scalar_t__ IN6_ARE_MASKED_ADDR_EQUAL (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int NPTV6_DYNAMIC_PREFIX ; 
 int NPTV6_READY ; 
 scalar_t__ SRV_OBJECT (struct ip_fw_chain*,int /*<<< orphan*/ ) ; 
 struct ip_fw_chain V_layer3_chain ; 
 int /*<<< orphan*/  if_ref (TYPE_1__*) ; 
 scalar_t__ nptv6_check_prefix (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nptv6_find_prefix (struct ip_fw_chain*,struct nptv6_cfg*,TYPE_1__*) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ifaddr_cb(struct namedobj_instance *ni, struct named_object *no,
    void *arg)
{
	struct ifaddr_event_args *args;
	struct ip_fw_chain *ch;
	struct nptv6_cfg *cfg;

	ch = &V_layer3_chain;
	cfg = (struct nptv6_cfg *)SRV_OBJECT(ch, no->kidx);
	if ((cfg->flags & NPTV6_DYNAMIC_PREFIX) == 0)
		return (0);

	args = arg;
	/* If interface name doesn't match, ignore */
	if (strncmp(args->ifp->if_xname, cfg->if_name, IF_NAMESIZE))
		return (0);
	if (args->ifp->if_flags & IFF_DYING) { /* XXX: is it possible? */
		cfg->flags &= ~NPTV6_READY;
		return (0);
	}
	if (args->event == IFADDR_EVENT_DEL) {
		/* If instance is not ready, ignore */
		if ((cfg->flags & NPTV6_READY) == 0)
			return (0);
		/* If address does not match the external prefix, ignore */
		if (IN6_ARE_MASKED_ADDR_EQUAL(&cfg->external, args->addr,
		    &cfg->mask) != 0)
			return (0);
		/* Otherwise clear READY flag */
		cfg->flags &= ~NPTV6_READY;
	} else {/* IFADDR_EVENT_ADD */
		/* If instance is already ready, ignore */
		if (cfg->flags & NPTV6_READY)
			return (0);
		/* If address is not suitable for prefix, ignore */
		if (nptv6_check_prefix(args->addr) ||
		    IN6_ARE_MASKED_ADDR_EQUAL(args->addr, &cfg->internal,
		    &cfg->mask))
			return (0);
		/* FALLTHROUGH */
	}
	MPASS(!(cfg->flags & NPTV6_READY));
	/* Try to determine the prefix */
	if_ref(args->ifp);
	nptv6_find_prefix(ch, cfg, args->ifp);
	return (0);
}