#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int /*<<< orphan*/  if_drv_flags; int /*<<< orphan*/  if_mtu; } ;
struct mlx4_en_tx_ring {int buf_size; scalar_t__ buf; } ;
struct TYPE_6__ {int /*<<< orphan*/  indir_qp; } ;
struct mlx4_en_priv {int port_up; int rx_ring_num; size_t port; int tx_ring_num; int num_tx_rings_p_up; int flags; TYPE_5__** rx_ring; struct mlx4_en_cq** rx_cq; struct mlx4_en_cq** tx_cq; struct mlx4_en_tx_ring** tx_ring; int /*<<< orphan*/  watchdog_timer; int /*<<< orphan*/  rx_mode_task; int /*<<< orphan*/  broadcast_id; TYPE_1__ rss_map; int /*<<< orphan*/  base_qpn; TYPE_4__* prof; int /*<<< orphan*/  rx_mb_size; int /*<<< orphan*/  counter_index; int /*<<< orphan*/  max_mtu; int /*<<< orphan*/  ethtool_list; int /*<<< orphan*/  curr_uc_list; int /*<<< orphan*/  curr_mc_list; int /*<<< orphan*/  uc_list; int /*<<< orphan*/  mc_list; struct mlx4_en_dev* mdev; } ;
struct mlx4_en_dev {int /*<<< orphan*/  workqueue; int /*<<< orphan*/  dev; scalar_t__* mac_removed; } ;
struct TYPE_8__ {int /*<<< orphan*/  cqn; } ;
struct mlx4_en_cq {int size; TYPE_3__ mcq; TYPE_2__* buf; } ;
struct TYPE_10__ {int /*<<< orphan*/  cqn; } ;
struct TYPE_9__ {int /*<<< orphan*/  rx_ppp; int /*<<< orphan*/  rx_pause; int /*<<< orphan*/  tx_ppp; int /*<<< orphan*/  tx_pause; } ;
struct TYPE_7__ {int /*<<< orphan*/  wqe_index; int /*<<< orphan*/  owner_sr_opcode; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  HW ; 
 int /*<<< orphan*/  IFF_DRV_OACTIVE ; 
 int /*<<< orphan*/  IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_OWNER_BIT ; 
 int /*<<< orphan*/  MLX4_CQE_OWNER_MASK ; 
 int MLX4_EN_FLAG_MC_PROMISC ; 
 int MLX4_EN_FLAG_PROMISC ; 
 int /*<<< orphan*/  MLX4_EN_WATCHDOG_TIMEOUT ; 
 int /*<<< orphan*/  MLX4_PROT_ETH ; 
 scalar_t__ STAMP_STRIDE ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mlx4_en_priv*) ; 
 int /*<<< orphan*/  cpu_to_be16 (int) ; 
 int /*<<< orphan*/  en_dbg (int /*<<< orphan*/ ,struct mlx4_en_priv*,char*,...) ; 
 int /*<<< orphan*/  en_err (struct mlx4_en_priv*,char*,...) ; 
 int /*<<< orphan*/  memset (size_t*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mlx4_INIT_PORT (int /*<<< orphan*/ ,size_t) ; 
 int mlx4_SET_PORT_general (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mlx4_SET_PORT_qpn_calc (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mlx4_en_activate_cq (struct mlx4_en_priv*,struct mlx4_en_cq*,int) ; 
 int mlx4_en_activate_rx_rings (struct mlx4_en_priv*) ; 
 int mlx4_en_activate_tx_ring (struct mlx4_en_priv*,struct mlx4_en_tx_ring*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlx4_en_arm_cq (struct mlx4_en_priv*,struct mlx4_en_cq*) ; 
 int /*<<< orphan*/  mlx4_en_calc_rx_buf (struct net_device*) ; 
 int mlx4_en_config_rss_steer (struct mlx4_en_priv*) ; 
 int /*<<< orphan*/  mlx4_en_cq_init_lock (struct mlx4_en_cq*) ; 
 int /*<<< orphan*/  mlx4_en_create_debug_files (struct mlx4_en_priv*) ; 
 int mlx4_en_create_drop_qp (struct mlx4_en_priv*) ; 
 int /*<<< orphan*/  mlx4_en_deactivate_cq (struct mlx4_en_priv*,struct mlx4_en_cq*) ; 
 int /*<<< orphan*/  mlx4_en_deactivate_rx_ring (struct mlx4_en_priv*,TYPE_5__*) ; 
 int /*<<< orphan*/  mlx4_en_deactivate_tx_ring (struct mlx4_en_priv*,struct mlx4_en_tx_ring*) ; 
 int /*<<< orphan*/  mlx4_en_destroy_drop_qp (struct mlx4_en_priv*) ; 
 int mlx4_en_get_qp (struct mlx4_en_priv*) ; 
 int /*<<< orphan*/  mlx4_en_put_qp (struct mlx4_en_priv*) ; 
 int /*<<< orphan*/  mlx4_en_release_rss_steer (struct mlx4_en_priv*) ; 
 int mlx4_en_set_cq_moder (struct mlx4_en_priv*,struct mlx4_en_cq*) ; 
 int /*<<< orphan*/  mlx4_en_watchdog_timeout ; 
 int /*<<< orphan*/  mlx4_get_default_counter_index (int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ mlx4_multicast_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx4_warn (struct mlx4_en_dev*,char*) ; 
 struct mlx4_en_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int mlx4_en_start_port(struct net_device *dev)
{
	struct mlx4_en_priv *priv = netdev_priv(dev);
	struct mlx4_en_dev *mdev = priv->mdev;
	struct mlx4_en_cq *cq;
	struct mlx4_en_tx_ring *tx_ring;
	int rx_index = 0;
	int tx_index = 0;
	int err = 0;
	int i;
	int j;
	u8 mc_list[16] = {0};


	if (priv->port_up) {
		en_dbg(DRV, priv, "start port called while port already up\n");
		return 0;
	}

	INIT_LIST_HEAD(&priv->mc_list);
	INIT_LIST_HEAD(&priv->uc_list);
	INIT_LIST_HEAD(&priv->curr_mc_list);
	INIT_LIST_HEAD(&priv->curr_uc_list);
	INIT_LIST_HEAD(&priv->ethtool_list);

	/* Calculate Rx buf size */
	dev->if_mtu = min(dev->if_mtu, priv->max_mtu);
        mlx4_en_calc_rx_buf(dev);
	en_dbg(DRV, priv, "Rx buf size:%d\n", priv->rx_mb_size);

	/* Configure rx cq's and rings */
	err = mlx4_en_activate_rx_rings(priv);
	if (err) {
		en_err(priv, "Failed to activate RX rings\n");
		return err;
	}
	for (i = 0; i < priv->rx_ring_num; i++) {
		cq = priv->rx_cq[i];

		mlx4_en_cq_init_lock(cq);
		err = mlx4_en_activate_cq(priv, cq, i);
		if (err) {
			en_err(priv, "Failed activating Rx CQ\n");
			goto cq_err;
		}
		for (j = 0; j < cq->size; j++)
			cq->buf[j].owner_sr_opcode = MLX4_CQE_OWNER_MASK;
		err = mlx4_en_set_cq_moder(priv, cq);
		if (err) {
			en_err(priv, "Failed setting cq moderation parameters");
			mlx4_en_deactivate_cq(priv, cq);
			goto cq_err;
		}
		mlx4_en_arm_cq(priv, cq);
		priv->rx_ring[i]->cqn = cq->mcq.cqn;
		++rx_index;
	}

	/* Set qp number */
	en_dbg(DRV, priv, "Getting qp number for port %d\n", priv->port);
	err = mlx4_en_get_qp(priv);
	if (err) {
		en_err(priv, "Failed getting eth qp\n");
		goto cq_err;
	}
	mdev->mac_removed[priv->port] = 0;

	priv->counter_index =
			mlx4_get_default_counter_index(mdev->dev, priv->port);

	err = mlx4_en_config_rss_steer(priv);
	if (err) {
		en_err(priv, "Failed configuring rss steering\n");
		goto mac_err;
	}

	err = mlx4_en_create_drop_qp(priv);
	if (err)
		goto rss_err;

	/* Configure tx cq's and rings */
	for (i = 0; i < priv->tx_ring_num; i++) {
		/* Configure cq */
		cq = priv->tx_cq[i];
		err = mlx4_en_activate_cq(priv, cq, i);
		if (err) {
			en_err(priv, "Failed activating Tx CQ\n");
			goto tx_err;
		}
		err = mlx4_en_set_cq_moder(priv, cq);
		if (err) {
			en_err(priv, "Failed setting cq moderation parameters");
			mlx4_en_deactivate_cq(priv, cq);
			goto tx_err;
		}
		en_dbg(DRV, priv, "Resetting index of collapsed CQ:%d to -1\n", i);
		cq->buf->wqe_index = cpu_to_be16(0xffff);

		/* Configure ring */
		tx_ring = priv->tx_ring[i];

		err = mlx4_en_activate_tx_ring(priv, tx_ring, cq->mcq.cqn,
					       i / priv->num_tx_rings_p_up);
		if (err) {
			en_err(priv, "Failed activating Tx ring %d\n", i);
			mlx4_en_deactivate_cq(priv, cq);
			goto tx_err;
		}

		/* Arm CQ for TX completions */
		mlx4_en_arm_cq(priv, cq);

		/* Set initial ownership of all Tx TXBBs to SW (1) */
		for (j = 0; j < tx_ring->buf_size; j += STAMP_STRIDE)
			*((u32 *) (tx_ring->buf + j)) = INIT_OWNER_BIT;
		++tx_index;
	}

	/* Configure port */
	err = mlx4_SET_PORT_general(mdev->dev, priv->port,
				    priv->rx_mb_size,
				    priv->prof->tx_pause,
				    priv->prof->tx_ppp,
				    priv->prof->rx_pause,
				    priv->prof->rx_ppp);
	if (err) {
		en_err(priv, "Failed setting port general configurations for port %d, with error %d\n",
		       priv->port, err);
		goto tx_err;
	}
	/* Set default qp number */
	err = mlx4_SET_PORT_qpn_calc(mdev->dev, priv->port, priv->base_qpn, 0);
	if (err) {
		en_err(priv, "Failed setting default qp numbers\n");
		goto tx_err;
	}

	/* Init port */
	en_dbg(HW, priv, "Initializing port\n");
	err = mlx4_INIT_PORT(mdev->dev, priv->port);
	if (err) {
		en_err(priv, "Failed Initializing port\n");
		goto tx_err;
	}

	/* Attach rx QP to bradcast address */
	memset(&mc_list[10], 0xff, ETH_ALEN);
	mc_list[5] = priv->port; /* needed for B0 steering support */
	if (mlx4_multicast_attach(mdev->dev, &priv->rss_map.indir_qp, mc_list,
				  priv->port, 0, MLX4_PROT_ETH,
				  &priv->broadcast_id))
		mlx4_warn(mdev, "Failed Attaching Broadcast\n");

	/* Must redo promiscuous mode setup. */
	priv->flags &= ~(MLX4_EN_FLAG_PROMISC | MLX4_EN_FLAG_MC_PROMISC);

	/* Schedule multicast task to populate multicast list */
	queue_work(mdev->workqueue, &priv->rx_mode_task);

	priv->port_up = true;

        /* Enable the queues. */
        dev->if_drv_flags &= ~IFF_DRV_OACTIVE;
        dev->if_drv_flags |= IFF_DRV_RUNNING;
#ifdef CONFIG_DEBUG_FS
	mlx4_en_create_debug_files(priv);
#endif
        callout_reset(&priv->watchdog_timer, MLX4_EN_WATCHDOG_TIMEOUT,
                    mlx4_en_watchdog_timeout, priv);


	return 0;

tx_err:
	while (tx_index--) {
		mlx4_en_deactivate_tx_ring(priv, priv->tx_ring[tx_index]);
		mlx4_en_deactivate_cq(priv, priv->tx_cq[tx_index]);
	}
	mlx4_en_destroy_drop_qp(priv);
rss_err:
	mlx4_en_release_rss_steer(priv);
mac_err:
	mlx4_en_put_qp(priv);
cq_err:
	while (rx_index--)
		mlx4_en_deactivate_cq(priv, priv->rx_cq[rx_index]);
	for (i = 0; i < priv->rx_ring_num; i++)
		mlx4_en_deactivate_rx_ring(priv, priv->rx_ring[i]);

	return err; /* need to close devices */
}