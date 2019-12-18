#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  ctx; } ;
struct TYPE_12__ {int /*<<< orphan*/  ctx; } ;
struct TYPE_11__ {int /*<<< orphan*/  ctx; } ;
struct TYPE_14__ {TYPE_5__ port_stats_debug; TYPE_4__ pport; TYPE_3__ vport; } ;
struct TYPE_9__ {int /*<<< orphan*/  tx_active_connections; } ;
struct TYPE_10__ {TYPE_1__ stats; } ;
struct mlx5e_priv {int gone; int /*<<< orphan*/  wq; int /*<<< orphan*/  cq_uar; int /*<<< orphan*/  mdev; int /*<<< orphan*/  pdn; int /*<<< orphan*/  tdn; int /*<<< orphan*/  mr; int /*<<< orphan*/  sysctl_ctx; TYPE_6__ stats; scalar_t__ sysctl_debug; int /*<<< orphan*/  media; int /*<<< orphan*/ * pfil; int /*<<< orphan*/ * vlan_detach; int /*<<< orphan*/ * vlan_attach; int /*<<< orphan*/  tstmp_clbr; int /*<<< orphan*/  watchdog; struct ifnet* ifp; TYPE_2__ rl; } ;
struct TYPE_15__ {int /*<<< orphan*/  num_comp_vectors; } ;
struct TYPE_16__ {TYPE_7__ eq_table; } ;
struct mlx5_core_dev {TYPE_8__ priv; } ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVENTHANDLER_DEREGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  M_MLX5EN ; 
 int /*<<< orphan*/  PRIV_LOCK (struct mlx5e_priv*) ; 
 int /*<<< orphan*/  PRIV_UNLOCK (struct mlx5e_priv*) ; 
 scalar_t__ READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ether_ifdetach (struct ifnet*) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct mlx5e_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  if_free (struct ifnet*) ; 
 int /*<<< orphan*/  ifmedia_removeall (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_core_dealloc_pd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_core_destroy_mkey (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_dealloc_transport_domain (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_en_err (struct ifnet*,char*) ; 
 int /*<<< orphan*/  mlx5_unmap_free_uar (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5e_close_locked (struct ifnet*) ; 
 int /*<<< orphan*/  mlx5e_disable_async_events (struct mlx5e_priv*) ; 
 int /*<<< orphan*/  mlx5e_priv_static_destroy (struct mlx5e_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5e_priv_wait_for_completion (struct mlx5e_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5e_rl_cleanup (struct mlx5e_priv*) ; 
 int /*<<< orphan*/  pause (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfil_head_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysctl_ctx_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlan_config ; 
 int /*<<< orphan*/  vlan_unconfig ; 

__attribute__((used)) static void
mlx5e_destroy_ifp(struct mlx5_core_dev *mdev, void *vpriv)
{
	struct mlx5e_priv *priv = vpriv;
	struct ifnet *ifp = priv->ifp;

	/* don't allow more IOCTLs */
	priv->gone = 1;

	/* XXX wait a bit to allow IOCTL handlers to complete */
	pause("W", hz);

#ifdef RATELIMIT
	/*
	 * The kernel can have reference(s) via the m_snd_tag's into
	 * the ratelimit channels, and these must go away before
	 * detaching:
	 */
	while (READ_ONCE(priv->rl.stats.tx_active_connections) != 0) {
		mlx5_en_err(priv->ifp,
		    "Waiting for all ratelimit connections to terminate\n");
		pause("W", hz);
	}
#endif
	/* wait for all unlimited send tags to complete */
	mlx5e_priv_wait_for_completion(priv, mdev->priv.eq_table.num_comp_vectors);

	/* stop watchdog timer */
	callout_drain(&priv->watchdog);

	callout_drain(&priv->tstmp_clbr);

	if (priv->vlan_attach != NULL)
		EVENTHANDLER_DEREGISTER(vlan_config, priv->vlan_attach);
	if (priv->vlan_detach != NULL)
		EVENTHANDLER_DEREGISTER(vlan_unconfig, priv->vlan_detach);

	/* make sure device gets closed */
	PRIV_LOCK(priv);
	mlx5e_close_locked(ifp);
	PRIV_UNLOCK(priv);

	/* deregister pfil */
	if (priv->pfil != NULL) {
		pfil_head_unregister(priv->pfil);
		priv->pfil = NULL;
	}

	/* unregister device */
	ifmedia_removeall(&priv->media);
	ether_ifdetach(ifp);

#ifdef RATELIMIT
	mlx5e_rl_cleanup(priv);
#endif
	/* destroy all remaining sysctl nodes */
	sysctl_ctx_free(&priv->stats.vport.ctx);
	sysctl_ctx_free(&priv->stats.pport.ctx);
	if (priv->sysctl_debug)
		sysctl_ctx_free(&priv->stats.port_stats_debug.ctx);
	sysctl_ctx_free(&priv->sysctl_ctx);

	mlx5_core_destroy_mkey(priv->mdev, &priv->mr);
	mlx5_dealloc_transport_domain(priv->mdev, priv->tdn);
	mlx5_core_dealloc_pd(priv->mdev, priv->pdn);
	mlx5_unmap_free_uar(priv->mdev, &priv->cq_uar);
	mlx5e_disable_async_events(priv);
	flush_workqueue(priv->wq);
	mlx5e_priv_static_destroy(priv, mdev->priv.eq_table.num_comp_vectors);
	if_free(ifp);
	free(priv, M_MLX5EN);
}