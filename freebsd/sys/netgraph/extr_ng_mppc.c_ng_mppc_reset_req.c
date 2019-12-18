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
struct TYPE_4__ {int bits; } ;
struct ng_mppc_dir {int flushed; TYPE_1__ cfg; int /*<<< orphan*/  key; int /*<<< orphan*/  rc4; int /*<<< orphan*/ * history; } ;
typedef  TYPE_2__* priv_p ;
typedef  int /*<<< orphan*/  node_p ;
struct TYPE_5__ {struct ng_mppc_dir xmit; } ;

/* Variables and functions */
 int /*<<< orphan*/  KEYLEN (int) ; 
 int /*<<< orphan*/  MPPC_InitCompressionHistory (int /*<<< orphan*/ *) ; 
 int MPPE_STATELESS ; 
 TYPE_2__* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rc4_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ng_mppc_reset_req(node_p node)
{   
	const priv_p priv = NG_NODE_PRIVATE(node);
	struct ng_mppc_dir *const d = &priv->xmit;

#ifdef NETGRAPH_MPPC_COMPRESSION
	if (d->history != NULL)
		MPPC_InitCompressionHistory(d->history);
#endif
#ifdef NETGRAPH_MPPC_ENCRYPTION
	if ((d->cfg.bits & MPPE_STATELESS) == 0)
		rc4_init(&d->rc4, d->key, KEYLEN(d->cfg.bits));
#endif
	d->flushed = 1;
}