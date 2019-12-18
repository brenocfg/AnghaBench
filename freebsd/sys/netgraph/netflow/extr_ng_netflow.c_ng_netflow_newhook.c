#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* priv_p ;
typedef  int /*<<< orphan*/  node_p ;
typedef  TYPE_3__* iface_p ;
typedef  void* hook_p ;
struct TYPE_6__ {int /*<<< orphan*/  ifinfo_dlt; } ;
struct TYPE_8__ {int /*<<< orphan*/ * out; TYPE_1__ info; int /*<<< orphan*/ * hook; } ;
struct TYPE_7__ {int /*<<< orphan*/  exp_callout; int /*<<< orphan*/ * export9; int /*<<< orphan*/ * export; TYPE_3__* ifaces; } ;

/* Variables and functions */
 scalar_t__ CNTR_MAX ; 
 int /*<<< orphan*/  DLT_EN10MB ; 
 int EINVAL ; 
 int EISCONN ; 
 int /*<<< orphan*/  NG_HOOK_SET_PRIVATE (void*,TYPE_3__*) ; 
 int /*<<< orphan*/  NG_NETFLOW_HOOK_DATA ; 
 int /*<<< orphan*/  NG_NETFLOW_HOOK_EXPORT ; 
 int /*<<< orphan*/  NG_NETFLOW_HOOK_EXPORT9 ; 
 int /*<<< orphan*/  NG_NETFLOW_HOOK_OUT ; 
 int NG_NETFLOW_MAXIFACES ; 
 TYPE_2__* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 scalar_t__ UINT64_MAX ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,void*) ; 
 int hz ; 
 int /*<<< orphan*/  isdigit (char const) ; 
 int /*<<< orphan*/  ng_netflow_expire ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 int strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (char const*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strtoul (char const*,char**,int) ; 

__attribute__((used)) static int
ng_netflow_newhook(node_p node, hook_p hook, const char *name)
{
	const priv_p priv = NG_NODE_PRIVATE(node);

	if (strncmp(name, NG_NETFLOW_HOOK_DATA,	/* an iface hook? */
	    strlen(NG_NETFLOW_HOOK_DATA)) == 0) {
		iface_p iface;
		int ifnum = -1;
		const char *cp;
		char *eptr;

		cp = name + strlen(NG_NETFLOW_HOOK_DATA);
		if (!isdigit(*cp) || (cp[0] == '0' && cp[1] != '\0'))
			return (EINVAL);

		ifnum = (int)strtoul(cp, &eptr, 10);
		if (*eptr != '\0' || ifnum < 0 || ifnum >= NG_NETFLOW_MAXIFACES)
			return (EINVAL);

		/* See if hook is already connected */
		if (priv->ifaces[ifnum].hook != NULL)
			return (EISCONN);

		iface = &priv->ifaces[ifnum];

		/* Link private info and hook together */
		NG_HOOK_SET_PRIVATE(hook, iface);
		iface->hook = hook;

		/*
		 * In most cases traffic accounting is done on an
		 * Ethernet interface, so default data link type
		 * will be DLT_EN10MB.
		 */
		iface->info.ifinfo_dlt = DLT_EN10MB;

	} else if (strncmp(name, NG_NETFLOW_HOOK_OUT,
	    strlen(NG_NETFLOW_HOOK_OUT)) == 0) {
		iface_p iface;
		int ifnum = -1;
		const char *cp;
		char *eptr;

		cp = name + strlen(NG_NETFLOW_HOOK_OUT);
		if (!isdigit(*cp) || (cp[0] == '0' && cp[1] != '\0'))
			return (EINVAL);

		ifnum = (int)strtoul(cp, &eptr, 10);
		if (*eptr != '\0' || ifnum < 0 || ifnum >= NG_NETFLOW_MAXIFACES)
			return (EINVAL);

		/* See if hook is already connected */
		if (priv->ifaces[ifnum].out != NULL)
			return (EISCONN);

		iface = &priv->ifaces[ifnum];

		/* Link private info and hook together */
		NG_HOOK_SET_PRIVATE(hook, iface);
		iface->out = hook;

	} else if (strcmp(name, NG_NETFLOW_HOOK_EXPORT) == 0) {

		if (priv->export != NULL)
			return (EISCONN);

		/* Netflow version 5 supports 32-bit counters only */
		if (CNTR_MAX == UINT64_MAX)
			return (EINVAL);

		priv->export = hook;

		/* Exporter is ready. Let's schedule expiry. */
		callout_reset(&priv->exp_callout, (1*hz), &ng_netflow_expire,
		    (void *)priv);
	} else if (strcmp(name, NG_NETFLOW_HOOK_EXPORT9) == 0) {

		if (priv->export9 != NULL)
			return (EISCONN);

		priv->export9 = hook;

		/* Exporter is ready. Let's schedule expiry. */
		callout_reset(&priv->exp_callout, (1*hz), &ng_netflow_expire,
		    (void *)priv);
	} else
		return (EINVAL);

	return (0);
}