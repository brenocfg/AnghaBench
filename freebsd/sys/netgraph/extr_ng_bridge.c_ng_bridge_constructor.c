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
struct TYPE_4__ {int debugLevel; int /*<<< orphan*/  minStableAge; int /*<<< orphan*/  maxStaleness; int /*<<< orphan*/  loopTimeout; } ;
struct TYPE_5__ {int numBuckets; int hashMask; int /*<<< orphan*/  timer; int /*<<< orphan*/  node; TYPE_1__ conf; void* tab; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_LOOP_TIMEOUT ; 
 int /*<<< orphan*/  DEFAULT_MAX_STALENESS ; 
 int /*<<< orphan*/  DEFAULT_MIN_STABLE_AGE ; 
 int MIN_BUCKETS ; 
 int /*<<< orphan*/  M_NETGRAPH_BRIDGE ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  NG_NODE_FORCE_WRITER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_NODE_SET_PRIVATE (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  hz ; 
 void* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ng_bridge_timeout ; 
 int /*<<< orphan*/  ng_callout (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ng_callout_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ng_bridge_constructor(node_p node)
{
	priv_p priv;

	/* Allocate and initialize private info */
	priv = malloc(sizeof(*priv), M_NETGRAPH_BRIDGE, M_WAITOK | M_ZERO);
	ng_callout_init(&priv->timer);

	/* Allocate and initialize hash table, etc. */
	priv->tab = malloc(MIN_BUCKETS * sizeof(*priv->tab),
	    M_NETGRAPH_BRIDGE, M_WAITOK | M_ZERO);
	priv->numBuckets = MIN_BUCKETS;
	priv->hashMask = MIN_BUCKETS - 1;
	priv->conf.debugLevel = 1;
	priv->conf.loopTimeout = DEFAULT_LOOP_TIMEOUT;
	priv->conf.maxStaleness = DEFAULT_MAX_STALENESS;
	priv->conf.minStableAge = DEFAULT_MIN_STABLE_AGE;

	/*
	 * This node has all kinds of stuff that could be screwed by SMP.
	 * Until it gets it's own internal protection, we go through in 
	 * single file. This could hurt a machine bridging between two 
	 * GB ethernets so it should be fixed. 
	 * When it's fixed the process SHOULD NOT SLEEP, spinlocks please!
	 * (and atomic ops )
	 */
	NG_NODE_FORCE_WRITER(node);
	NG_NODE_SET_PRIVATE(node, priv);
	priv->node = node;

	/* Start timer; timer is always running while node is alive */
	ng_callout(&priv->timer, node, NULL, hz, ng_bridge_timeout, NULL, 0);

	/* Done */
	return (0);
}