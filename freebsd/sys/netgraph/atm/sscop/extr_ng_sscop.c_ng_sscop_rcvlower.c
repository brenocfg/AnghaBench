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
struct TYPE_2__ {int /*<<< orphan*/  in_dropped; int /*<<< orphan*/  in_packets; } ;
struct priv {TYPE_1__ stats; int /*<<< orphan*/  sscop; int /*<<< orphan*/ * upper; int /*<<< orphan*/  enabled; } ;
struct mbuf {int dummy; } ;
typedef  int /*<<< orphan*/  item_p ;
typedef  int /*<<< orphan*/  hook_p ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  NGI_GET_M (int /*<<< orphan*/ ,struct mbuf*) ; 
 int /*<<< orphan*/  NG_FREE_ITEM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_HOOK_NODE (int /*<<< orphan*/ ) ; 
 struct priv* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 scalar_t__ SSCOP_IDLE ; 
 scalar_t__ sscop_getstate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sscop_input (int /*<<< orphan*/ ,struct mbuf*) ; 

__attribute__((used)) static int
ng_sscop_rcvlower(hook_p hook, item_p item)
{
	struct priv *priv = NG_NODE_PRIVATE(NG_HOOK_NODE(hook));
	struct mbuf *m;

	if (!priv->enabled) {
		NG_FREE_ITEM(item);
		return EINVAL;
	}

	/*
	 * If we are disconnected at the upper layer and in the IDLE
	 * state, drop any incoming packet.
	 */
	if (priv->upper != NULL || sscop_getstate(priv->sscop) != SSCOP_IDLE) {
		NGI_GET_M(item, m);
		priv->stats.in_packets++;
		sscop_input(priv->sscop, m);
	} else {
		priv->stats.in_dropped++;
	}
	NG_FREE_ITEM(item);

	return (0);
}