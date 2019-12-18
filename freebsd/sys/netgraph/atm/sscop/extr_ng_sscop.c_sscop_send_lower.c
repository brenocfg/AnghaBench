#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sscop {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  out_packets; int /*<<< orphan*/  out_dropped; } ;
struct priv {int /*<<< orphan*/ * lower; TYPE_1__ stats; } ;
struct mbuf {int dummy; } ;
typedef  int /*<<< orphan*/  node_p ;

/* Variables and functions */
 struct priv* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_SEND_DATA_ONLY (int,int /*<<< orphan*/ *,struct mbuf*) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 

__attribute__((used)) static void
sscop_send_lower(struct sscop *sscop, void *p, struct mbuf *m)
{
	node_p node = (node_p)p;
	struct priv *priv = NG_NODE_PRIVATE(node);
	int error;

	if (priv->lower == NULL) {
		m_freem(m);
		priv->stats.out_dropped++;
		return;
	}

	priv->stats.out_packets++;
	NG_SEND_DATA_ONLY(error, priv->lower, m);
}