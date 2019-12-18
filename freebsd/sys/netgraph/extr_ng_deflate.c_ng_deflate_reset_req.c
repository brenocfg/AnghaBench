#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* priv_p ;
typedef  int /*<<< orphan*/  node_p ;
struct TYPE_4__ {scalar_t__ enable; } ;
struct TYPE_5__ {int /*<<< orphan*/  cx; scalar_t__ compress; TYPE_1__ cfg; scalar_t__ seqnum; } ;

/* Variables and functions */
 TYPE_2__* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  deflateReset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  inflateReset (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ng_deflate_reset_req(node_p node)
{
	const priv_p priv = NG_NODE_PRIVATE(node);

	priv->seqnum = 0;
	if (priv->cfg.enable) {
	    if (priv->compress)
		deflateReset(&priv->cx);
	    else
		inflateReset(&priv->cx);
	}
}