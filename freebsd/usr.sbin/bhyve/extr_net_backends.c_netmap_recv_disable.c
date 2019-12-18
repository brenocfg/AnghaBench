#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct netmap_priv {int /*<<< orphan*/  mevp; } ;
struct net_backend {scalar_t__ opaque; } ;

/* Variables and functions */
 int /*<<< orphan*/  mevent_disable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
netmap_recv_disable(struct net_backend *be)
{
	struct netmap_priv *priv = (struct netmap_priv *)be->opaque;

	mevent_disable(priv->mevp);
}