#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mbuf {int dummy; } ;
typedef  TYPE_1__* priv_p ;
typedef  int /*<<< orphan*/  node_p ;
struct TYPE_3__ {int /*<<< orphan*/  lower; } ;

/* Variables and functions */
 TYPE_1__* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_SEND_DATA_ONLY (int,int /*<<< orphan*/ ,struct mbuf*) ; 
 int ng_gif_glue_af (struct mbuf**,int) ; 

__attribute__((used)) static void
ng_gif_input2(node_p node, struct mbuf **mp, int af)
{
	const priv_p priv = NG_NODE_PRIVATE(node);
	int error;

	/* Glue address family on */
	if ((error = ng_gif_glue_af(mp, af)) != 0)
		return;

	/* Send out lower/orphan hook */
	NG_SEND_DATA_ONLY(error, priv->lower, *mp);
	*mp = NULL;
}