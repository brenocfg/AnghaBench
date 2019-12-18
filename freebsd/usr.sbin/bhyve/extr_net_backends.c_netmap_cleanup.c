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
struct netmap_priv {scalar_t__ nmd; scalar_t__ mevp; } ;
struct net_backend {int fd; scalar_t__ opaque; } ;

/* Variables and functions */
 int /*<<< orphan*/  mevent_delete (scalar_t__) ; 
 int /*<<< orphan*/  nm_close (scalar_t__) ; 

__attribute__((used)) static void
netmap_cleanup(struct net_backend *be)
{
	struct netmap_priv *priv = (struct netmap_priv *)be->opaque;

	if (priv->mevp) {
		mevent_delete(priv->mevp);
	}
	if (priv->nmd) {
		nm_close(priv->nmd);
	}
	be->fd = -1;
}