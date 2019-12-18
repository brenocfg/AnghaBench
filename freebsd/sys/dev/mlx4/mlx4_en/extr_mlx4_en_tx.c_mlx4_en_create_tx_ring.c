#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_9__ ;
typedef  struct TYPE_25__   TYPE_8__ ;
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_13__ ;
typedef  struct TYPE_16__   TYPE_11__ ;
typedef  struct TYPE_15__   TYPE_10__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_23__ {scalar_t__ map; int /*<<< orphan*/  buf; } ;
struct TYPE_16__ {TYPE_6__ direct; } ;
struct TYPE_15__ {TYPE_11__ buf; } ;
struct TYPE_17__ {TYPE_7__* uar; } ;
struct TYPE_26__ {int /*<<< orphan*/  event; } ;
struct TYPE_22__ {int /*<<< orphan*/  m; } ;
struct TYPE_21__ {int /*<<< orphan*/  m; } ;
struct mlx4_en_tx_ring {int size; int size_mask; int stride; int bf_enabled; int queue_index; int /*<<< orphan*/  dma_tag; TYPE_8__* tx_info; int /*<<< orphan*/  buf_size; TYPE_10__ wqres; int /*<<< orphan*/  qpn; TYPE_13__ bf; TYPE_9__ qp; int /*<<< orphan*/  buf; TYPE_5__ comp_lock; TYPE_4__ tx_lock; int /*<<< orphan*/  inline_thold; } ;
struct mlx4_en_tx_info {int dummy; } ;
struct mlx4_en_priv {TYPE_3__* prof; struct mlx4_en_dev* mdev; } ;
struct TYPE_24__ {int /*<<< orphan*/  map; } ;
struct mlx4_en_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  uar_map; TYPE_7__ priv_uar; TYPE_2__* pdev; } ;
struct TYPE_25__ {int /*<<< orphan*/  dma_map; } ;
struct TYPE_20__ {int /*<<< orphan*/  inline_thold; } ;
struct TYPE_18__ {int /*<<< orphan*/  bsddev; } ;
struct TYPE_19__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALIGN (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  DRV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MAX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX_INLINE ; 
 int /*<<< orphan*/  MIN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MIN_PKT_LEN ; 
 int /*<<< orphan*/  MLX4_EN_PAGE_SIZE ; 
 int /*<<< orphan*/  MLX4_EN_TX_MAX_MBUF_FRAGS ; 
 int /*<<< orphan*/  MLX4_EN_TX_MAX_MBUF_SIZE ; 
 int /*<<< orphan*/  MLX4_EN_TX_MAX_PAYLOAD_SIZE ; 
 int /*<<< orphan*/  MLX4_RESERVE_ETH_BF_QP ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int PAGE_SIZE ; 
 int bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ ) ; 
 int bus_dmamap_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamap_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  en_dbg (int /*<<< orphan*/ ,struct mlx4_en_priv*,char*,...) ; 
 int /*<<< orphan*/  en_err (struct mlx4_en_priv*,char*,...) ; 
 int /*<<< orphan*/  kfree (struct mlx4_en_tx_ring*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 void* kzalloc_node (int,int /*<<< orphan*/ ,int) ; 
 int mlx4_alloc_hwq_res (int /*<<< orphan*/ ,TYPE_10__*,int /*<<< orphan*/ ,int) ; 
 int mlx4_bf_alloc (int /*<<< orphan*/ ,TYPE_13__*,int) ; 
 int mlx4_en_map_buffer (TYPE_11__*) ; 
 int /*<<< orphan*/  mlx4_en_sqp_event ; 
 int /*<<< orphan*/  mlx4_en_unmap_buffer (TYPE_11__*) ; 
 int /*<<< orphan*/  mlx4_free_hwq_res (int /*<<< orphan*/ ,TYPE_10__*,int /*<<< orphan*/ ) ; 
 int mlx4_qp_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_9__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx4_qp_release_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int mlx4_qp_reserve_range (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfree (TYPE_8__*) ; 

int mlx4_en_create_tx_ring(struct mlx4_en_priv *priv,
			   struct mlx4_en_tx_ring **pring, u32 size,
			   u16 stride, int node, int queue_idx)
{
	struct mlx4_en_dev *mdev = priv->mdev;
	struct mlx4_en_tx_ring *ring;
	uint32_t x;
	int tmp;
	int err;

	ring = kzalloc_node(sizeof(struct mlx4_en_tx_ring), GFP_KERNEL, node);
	if (!ring) {
		ring = kzalloc(sizeof(struct mlx4_en_tx_ring), GFP_KERNEL);
		if (!ring) {
			en_err(priv, "Failed allocating TX ring\n");
			return -ENOMEM;
		}
	}

	/* Create DMA descriptor TAG */
	if ((err = -bus_dma_tag_create(
	    bus_get_dma_tag(mdev->pdev->dev.bsddev),
	    1,					/* any alignment */
	    0,					/* no boundary */
	    BUS_SPACE_MAXADDR,			/* lowaddr */
	    BUS_SPACE_MAXADDR,			/* highaddr */
	    NULL, NULL,				/* filter, filterarg */
	    MLX4_EN_TX_MAX_PAYLOAD_SIZE,	/* maxsize */
	    MLX4_EN_TX_MAX_MBUF_FRAGS,		/* nsegments */
	    MLX4_EN_TX_MAX_MBUF_SIZE,		/* maxsegsize */
	    0,					/* flags */
	    NULL, NULL,				/* lockfunc, lockfuncarg */
	    &ring->dma_tag)))
		goto done;

	ring->size = size;
	ring->size_mask = size - 1;
	ring->stride = stride;
	ring->inline_thold = MAX(MIN_PKT_LEN, MIN(priv->prof->inline_thold, MAX_INLINE));
	mtx_init(&ring->tx_lock.m, "mlx4 tx", NULL, MTX_DEF);
	mtx_init(&ring->comp_lock.m, "mlx4 comp", NULL, MTX_DEF);

	tmp = size * sizeof(struct mlx4_en_tx_info);
	ring->tx_info = kzalloc_node(tmp, GFP_KERNEL, node);
	if (!ring->tx_info) {
		ring->tx_info = kzalloc(tmp, GFP_KERNEL);
		if (!ring->tx_info) {
			err = -ENOMEM;
			goto err_ring;
		}
	}

	/* Create DMA descriptor MAPs */
	for (x = 0; x != size; x++) {
		err = -bus_dmamap_create(ring->dma_tag, 0,
		    &ring->tx_info[x].dma_map);
		if (err != 0) {
			while (x--) {
				bus_dmamap_destroy(ring->dma_tag,
				    ring->tx_info[x].dma_map);
			}
			goto err_info;
		}
	}

	en_dbg(DRV, priv, "Allocated tx_info ring at addr:%p size:%d\n",
		 ring->tx_info, tmp);

	ring->buf_size = ALIGN(size * ring->stride, MLX4_EN_PAGE_SIZE);

	/* Allocate HW buffers on provided NUMA node */
	err = mlx4_alloc_hwq_res(mdev->dev, &ring->wqres, ring->buf_size,
				 2 * PAGE_SIZE);
	if (err) {
		en_err(priv, "Failed allocating hwq resources\n");
		goto err_dma_map;
	}

	err = mlx4_en_map_buffer(&ring->wqres.buf);
	if (err) {
		en_err(priv, "Failed to map TX buffer\n");
		goto err_hwq_res;
	}

	ring->buf = ring->wqres.buf.direct.buf;

	en_dbg(DRV, priv, "Allocated TX ring (addr:%p) - buf:%p size:%d "
	       "buf_size:%d dma:%llx\n", ring, ring->buf, ring->size,
	       ring->buf_size, (unsigned long long) ring->wqres.buf.direct.map);

	err = mlx4_qp_reserve_range(mdev->dev, 1, 1, &ring->qpn,
				    MLX4_RESERVE_ETH_BF_QP);
	if (err) {
		en_err(priv, "failed reserving qp for TX ring\n");
		goto err_map;
	}

	err = mlx4_qp_alloc(mdev->dev, ring->qpn, &ring->qp, GFP_KERNEL);
	if (err) {
		en_err(priv, "Failed allocating qp %d\n", ring->qpn);
		goto err_reserve;
	}
	ring->qp.event = mlx4_en_sqp_event;

	err = mlx4_bf_alloc(mdev->dev, &ring->bf, node);
	if (err) {
		en_dbg(DRV, priv, "working without blueflame (%d)", err);
		ring->bf.uar = &mdev->priv_uar;
		ring->bf.uar->map = mdev->uar_map;
		ring->bf_enabled = false;
	} else
		ring->bf_enabled = true;
	ring->queue_index = queue_idx;

	*pring = ring;
	return 0;

err_reserve:
	mlx4_qp_release_range(mdev->dev, ring->qpn, 1);
err_map:
	mlx4_en_unmap_buffer(&ring->wqres.buf);
err_hwq_res:
	mlx4_free_hwq_res(mdev->dev, &ring->wqres, ring->buf_size);
err_dma_map:
	for (x = 0; x != size; x++)
		bus_dmamap_destroy(ring->dma_tag, ring->tx_info[x].dma_map);
err_info:
	vfree(ring->tx_info);
err_ring:
	bus_dma_tag_destroy(ring->dma_tag);
done:
	kfree(ring);
	return err;
}