#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* sc_p ;
typedef  int /*<<< orphan*/  node_p ;
struct TYPE_6__ {int /*<<< orphan*/  ifq_mtx; } ;
struct TYPE_5__ {TYPE_4__ outq; int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFQ_SET_MAXLEN (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  M_NETGRAPH ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  NG_NODE_SET_PRIVATE (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  ifqmaxlen ; 
 TYPE_1__* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ngt_constructor(node_p node)
{
	sc_p sc;

	/* Allocate private structure */
	sc = malloc(sizeof(*sc), M_NETGRAPH, M_WAITOK | M_ZERO);

	NG_NODE_SET_PRIVATE(node, sc);
	sc->node = node;

	mtx_init(&sc->outq.ifq_mtx, "ng_tty node+queue", NULL, MTX_DEF);
	IFQ_SET_MAXLEN(&sc->outq, ifqmaxlen);

	return (0);
}