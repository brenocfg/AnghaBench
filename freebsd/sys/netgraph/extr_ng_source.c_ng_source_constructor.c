#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* sc_p ;
typedef  int /*<<< orphan*/  node_p ;
struct TYPE_5__ {int ifq_maxlen; } ;
struct TYPE_6__ {int /*<<< orphan*/  intr_ch; TYPE_1__ snd_queue; int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_NETGRAPH ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  NG_NODE_SET_PRIVATE (int /*<<< orphan*/ ,TYPE_2__*) ; 
 TYPE_2__* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ng_callout_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ng_source_constructor(node_p node)
{
	sc_p sc;

	sc = malloc(sizeof(*sc), M_NETGRAPH, M_WAITOK | M_ZERO);

	NG_NODE_SET_PRIVATE(node, sc);
	sc->node = node;
	sc->snd_queue.ifq_maxlen = 2048;	/* XXX not checked */
	ng_callout_init(&sc->intr_ch);

	return (0);
}