#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* priv_p ;
typedef  int /*<<< orphan*/  node_p ;
struct TYPE_4__ {int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_NG_PIPE ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  NG_NODE_FORCE_WRITER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_NODE_SET_PRIVATE (int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_1__* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ng_callout_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ngp_constructor(node_p node)
{
	priv_p priv;

	priv = malloc(sizeof(*priv), M_NG_PIPE, M_ZERO | M_WAITOK);
	NG_NODE_SET_PRIVATE(node, priv);

	/* Mark node as single-threaded */
	NG_NODE_FORCE_WRITER(node);

	ng_callout_init(&priv->timer);

	return (0);
}