#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_5__* priv_p ;
typedef  int /*<<< orphan*/  node_p ;
struct TYPE_9__ {scalar_t__ mode; void* red_action; void* yellow_action; void* green_action; void* cir; void* ebs; void* cbs; } ;
struct TYPE_11__ {int /*<<< orphan*/  q_mtx; int /*<<< orphan*/  q_callout; scalar_t__ q_last; scalar_t__ q_first; int /*<<< orphan*/  lastRefill; TYPE_2__ conf; void* te; void* tc; int /*<<< orphan*/ * dest; int /*<<< orphan*/ * hook; } ;
struct TYPE_8__ {scalar_t__ mode; void* red_action; void* yellow_action; void* green_action; void* cir; void* ebs; void* cbs; } ;
struct TYPE_10__ {int /*<<< orphan*/  lastRefill; int /*<<< orphan*/  q_mtx; int /*<<< orphan*/  q_callout; scalar_t__ q_last; scalar_t__ q_first; TYPE_1__ conf; void* te; void* tc; int /*<<< orphan*/ * dest; int /*<<< orphan*/ * hook; } ;
struct TYPE_12__ {TYPE_4__ lower; TYPE_3__ upper; int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  M_NETGRAPH ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 void* NG_CAR_ACTION_DROP ; 
 void* NG_CAR_ACTION_FORWARD ; 
 void* NG_CAR_CBS_MIN ; 
 void* NG_CAR_CIR_DFLT ; 
 void* NG_CAR_EBS_MIN ; 
 int /*<<< orphan*/  NG_NODE_SET_PRIVATE (int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  getbinuptime (int /*<<< orphan*/ *) ; 
 TYPE_5__* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ng_callout_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ng_car_constructor(node_p node)
{
	priv_p priv;

	/* Initialize private descriptor. */
	priv = malloc(sizeof(*priv), M_NETGRAPH, M_WAITOK | M_ZERO);

	NG_NODE_SET_PRIVATE(node, priv);
	priv->node = node;

	/*
	 * Arbitrary default values
	 */

	priv->upper.hook = NULL;
	priv->upper.dest = NULL;
	priv->upper.tc = priv->upper.conf.cbs = NG_CAR_CBS_MIN;
	priv->upper.te = priv->upper.conf.ebs = NG_CAR_EBS_MIN;
	priv->upper.conf.cir = NG_CAR_CIR_DFLT;
	priv->upper.conf.green_action = NG_CAR_ACTION_FORWARD;
	priv->upper.conf.yellow_action = NG_CAR_ACTION_FORWARD;
	priv->upper.conf.red_action = NG_CAR_ACTION_DROP;
	priv->upper.conf.mode = 0;
	getbinuptime(&priv->upper.lastRefill);
	priv->upper.q_first = 0;
	priv->upper.q_last = 0;
	ng_callout_init(&priv->upper.q_callout);
	mtx_init(&priv->upper.q_mtx, "ng_car_u", NULL, MTX_DEF);

	priv->lower.hook = NULL;
	priv->lower.dest = NULL;
	priv->lower.tc = priv->lower.conf.cbs = NG_CAR_CBS_MIN;
	priv->lower.te = priv->lower.conf.ebs = NG_CAR_EBS_MIN;
	priv->lower.conf.cir = NG_CAR_CIR_DFLT;
	priv->lower.conf.green_action = NG_CAR_ACTION_FORWARD;
	priv->lower.conf.yellow_action = NG_CAR_ACTION_FORWARD;
	priv->lower.conf.red_action = NG_CAR_ACTION_DROP;
	priv->lower.conf.mode = 0;
	priv->lower.lastRefill = priv->upper.lastRefill;
	priv->lower.q_first = 0;
	priv->lower.q_last = 0;
	ng_callout_init(&priv->lower.q_callout);
	mtx_init(&priv->lower.q_mtx, "ng_car_l", NULL, MTX_DEF);

	return (0);
}