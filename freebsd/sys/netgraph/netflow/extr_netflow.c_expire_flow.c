#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
struct netflow_export_item {int /*<<< orphan*/  item9_opt; int /*<<< orphan*/ * item9; int /*<<< orphan*/ * item; } ;
struct TYPE_11__ {scalar_t__ version; } ;
struct flow_entry {TYPE_1__ f; } ;
typedef  TYPE_2__* priv_p ;
typedef  int /*<<< orphan*/  fib_export_p ;
struct TYPE_12__ {int /*<<< orphan*/  zone6; int /*<<< orphan*/  zone; int /*<<< orphan*/  nfinfo_export9_failed; int /*<<< orphan*/ * export9; int /*<<< orphan*/  nfinfo_export_failed; int /*<<< orphan*/ * export; } ;

/* Variables and functions */
 scalar_t__ IP6VERSION ; 
 scalar_t__ IPVERSION ; 
 int /*<<< orphan*/  NG_QUEUE ; 
 scalar_t__ export9_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct flow_entry*) ; 
 int /*<<< orphan*/  export9_send (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ export_add (int /*<<< orphan*/ *,struct flow_entry*) ; 
 int /*<<< orphan*/  export_send (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * get_export9_dgram (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * get_export_dgram (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*,scalar_t__) ; 
 int /*<<< orphan*/  return_export9_dgram (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  return_export_dgram (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uma_zfree_arg (int /*<<< orphan*/ ,struct flow_entry*,TYPE_2__*) ; 

__attribute__((used)) static void
expire_flow(priv_p priv, fib_export_p fe, struct flow_entry *fle, int flags)
{
	struct netflow_export_item exp;
	uint16_t version = fle->f.version;

	if ((priv->export != NULL) && (version == IPVERSION)) {
		exp.item = get_export_dgram(priv, fe);
		if (exp.item == NULL) {
			priv->nfinfo_export_failed++;
			if (priv->export9 != NULL)
				priv->nfinfo_export9_failed++;
			/* fle definitely contains IPv4 flow. */
			uma_zfree_arg(priv->zone, fle, priv);
			return;
		}

		if (export_add(exp.item, fle) > 0)
			export_send(priv, fe, exp.item, flags);
		else
			return_export_dgram(priv, fe, exp.item, NG_QUEUE);
	}

	if (priv->export9 != NULL) {
		exp.item9 = get_export9_dgram(priv, fe, &exp.item9_opt);
		if (exp.item9 == NULL) {
			priv->nfinfo_export9_failed++;
			if (version == IPVERSION)
				uma_zfree_arg(priv->zone, fle, priv);
#ifdef INET6
			else if (version == IP6VERSION)
				uma_zfree_arg(priv->zone6, fle, priv);
#endif
			else
				panic("ng_netflow: Unknown IP proto: %d",
				    version);
			return;
		}

		if (export9_add(exp.item9, exp.item9_opt, fle) > 0)
			export9_send(priv, fe, exp.item9, exp.item9_opt, flags);
		else
			return_export9_dgram(priv, fe, exp.item9,
			    exp.item9_opt, NG_QUEUE);
	}

	if (version == IPVERSION)
		uma_zfree_arg(priv->zone, fle, priv);
#ifdef INET6
	else if (version == IP6VERSION)
		uma_zfree_arg(priv->zone6, fle, priv);
#endif
}