#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  enableMultilink; int /*<<< orphan*/  recvShortSeq; int /*<<< orphan*/  xmitShortSeq; } ;
struct ng_ppp_node_conf {TYPE_4__ bund; TYPE_2__* links; } ;
typedef  TYPE_5__* priv_p ;
typedef  int /*<<< orphan*/  node_p ;
struct TYPE_9__ {int /*<<< orphan*/  recvShortSeq; int /*<<< orphan*/  xmitShortSeq; int /*<<< orphan*/  enableMultilink; } ;
struct TYPE_11__ {scalar_t__ numActiveLinks; TYPE_3__ conf; TYPE_1__* links; } ;
struct TYPE_8__ {scalar_t__ mru; scalar_t__ bandwidth; scalar_t__ latency; scalar_t__ enableLink; } ;
struct TYPE_7__ {int /*<<< orphan*/ * hook; } ;

/* Variables and functions */
 scalar_t__ MP_MIN_LINK_MRU ; 
 TYPE_5__* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 scalar_t__ NG_PPP_MAX_BANDWIDTH ; 
 scalar_t__ NG_PPP_MAX_LATENCY ; 
 int NG_PPP_MAX_LINKS ; 

__attribute__((used)) static int
ng_ppp_config_valid(node_p node, const struct ng_ppp_node_conf *newConf)
{
	const priv_p priv = NG_NODE_PRIVATE(node);
	int i, newNumLinksActive;

	/* Check per-link config and count how many links would be active */
	for (newNumLinksActive = i = 0; i < NG_PPP_MAX_LINKS; i++) {
		if (newConf->links[i].enableLink && priv->links[i].hook != NULL)
			newNumLinksActive++;
		if (!newConf->links[i].enableLink)
			continue;
		if (newConf->links[i].mru < MP_MIN_LINK_MRU)
			return (0);
		if (newConf->links[i].bandwidth == 0)
			return (0);
		if (newConf->links[i].bandwidth > NG_PPP_MAX_BANDWIDTH)
			return (0);
		if (newConf->links[i].latency > NG_PPP_MAX_LATENCY)
			return (0);
	}

	/* Disallow changes to multi-link configuration while MP is active */
	if (priv->numActiveLinks > 0 && newNumLinksActive > 0) {
		if (!priv->conf.enableMultilink
				!= !newConf->bund.enableMultilink
		    || !priv->conf.xmitShortSeq != !newConf->bund.xmitShortSeq
		    || !priv->conf.recvShortSeq != !newConf->bund.recvShortSeq)
			return (0);
	}

	/* At most one link can be active unless multi-link is enabled */
	if (!newConf->bund.enableMultilink && newNumLinksActive > 1)
		return (0);

	/* Configuration change would be valid */
	return (1);
}