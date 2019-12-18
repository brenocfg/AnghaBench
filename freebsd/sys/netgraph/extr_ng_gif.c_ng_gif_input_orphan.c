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
struct ifnet {int dummy; } ;
typedef  TYPE_1__* priv_p ;
typedef  int /*<<< orphan*/  node_p ;
struct TYPE_3__ {int /*<<< orphan*/  lowerOrphan; int /*<<< orphan*/ * lower; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFP2NG (struct ifnet*) ; 
 TYPE_1__* NG_NODE_PRIVATE (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int /*<<< orphan*/  ng_gif_input2 (int /*<<< orphan*/  const,struct mbuf**,int) ; 

__attribute__((used)) static void
ng_gif_input_orphan(struct ifnet *ifp, struct mbuf *m, int af)
{
	const node_p node = IFP2NG(ifp);
	const priv_p priv = NG_NODE_PRIVATE(node);

	/* If "orphan" hook not connected, let packet continue */
	if (priv->lower == NULL || !priv->lowerOrphan) {
		m_freem(m);
		return;
	}
	ng_gif_input2(node, &m, af);
	if (m != NULL)
		m_freem(m);
}