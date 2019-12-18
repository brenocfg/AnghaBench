#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int u32 ;
struct TYPE_13__ {int /*<<< orphan*/  dma_map; } ;
struct TYPE_12__ {int /*<<< orphan*/  buf; } ;
struct TYPE_16__ {TYPE_3__ direct; } ;
struct TYPE_15__ {TYPE_7__ buf; } ;
struct mlx4_en_rx_ring {int size; int size_mask; int /*<<< orphan*/  dma_tag; TYPE_5__* mbuf; TYPE_4__ spare; scalar_t__ buf_size; TYPE_6__ wqres; int /*<<< orphan*/  buf; int /*<<< orphan*/  log_stride; scalar_t__ cons; scalar_t__ prod; } ;
struct mlx4_en_rx_mbuf {int dummy; } ;
struct mlx4_en_rx_desc {int dummy; } ;
struct mlx4_en_priv {struct mlx4_en_dev* mdev; } ;
struct mlx4_en_dev {int /*<<< orphan*/  dev; TYPE_2__* pdev; } ;
struct TYPE_14__ {int /*<<< orphan*/  dma_map; } ;
struct TYPE_10__ {int /*<<< orphan*/  bsddev; } ;
struct TYPE_11__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  DRV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MJUM16BYTES ; 
 int /*<<< orphan*/  MLX4_EN_MAX_RX_SEGS ; 
 int PAGE_SIZE ; 
 scalar_t__ TXBB_SIZE ; 
 int bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ ) ; 
 int bus_dmamap_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamap_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  en_dbg (int /*<<< orphan*/ ,struct mlx4_en_priv*,char*,TYPE_5__*,int) ; 
 int /*<<< orphan*/  en_err (struct mlx4_en_priv*,char*) ; 
 int /*<<< orphan*/  ilog2 (int) ; 
 int /*<<< orphan*/  kfree (struct mlx4_en_rx_ring*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int mlx4_alloc_hwq_res (int /*<<< orphan*/ ,TYPE_6__*,scalar_t__,int) ; 
 int mlx4_en_map_buffer (TYPE_7__*) ; 
 int /*<<< orphan*/  mlx4_free_hwq_res (int /*<<< orphan*/ ,TYPE_6__*,scalar_t__) ; 
 int /*<<< orphan*/  vfree (TYPE_5__*) ; 

int mlx4_en_create_rx_ring(struct mlx4_en_priv *priv,
			   struct mlx4_en_rx_ring **pring,
			   u32 size, int node)
{
	struct mlx4_en_dev *mdev = priv->mdev;
	struct mlx4_en_rx_ring *ring;
	int err;
	int tmp;
	uint32_t x;

        ring = kzalloc(sizeof(struct mlx4_en_rx_ring), GFP_KERNEL);
        if (!ring) {
                en_err(priv, "Failed to allocate RX ring structure\n");
                return -ENOMEM;
        }

	/* Create DMA descriptor TAG */
	if ((err = -bus_dma_tag_create(
	    bus_get_dma_tag(mdev->pdev->dev.bsddev),
	    1,				/* any alignment */
	    0,				/* no boundary */
	    BUS_SPACE_MAXADDR,		/* lowaddr */
	    BUS_SPACE_MAXADDR,		/* highaddr */
	    NULL, NULL,			/* filter, filterarg */
	    MJUM16BYTES,		/* maxsize */
	    MLX4_EN_MAX_RX_SEGS,	/* nsegments */
	    MJUM16BYTES,		/* maxsegsize */
	    0,				/* flags */
	    NULL, NULL,			/* lockfunc, lockfuncarg */
	    &ring->dma_tag))) {
		en_err(priv, "Failed to create DMA tag\n");
		goto err_ring;
	}

	ring->prod = 0;
	ring->cons = 0;
	ring->size = size;
	ring->size_mask = size - 1;

	ring->log_stride = ilog2(sizeof(struct mlx4_en_rx_desc));
	ring->buf_size = (ring->size * sizeof(struct mlx4_en_rx_desc)) + TXBB_SIZE;

	tmp = size * sizeof(struct mlx4_en_rx_mbuf);

        ring->mbuf = kzalloc(tmp, GFP_KERNEL);
        if (ring->mbuf == NULL) {
                err = -ENOMEM;
                goto err_dma_tag;
        }

	err = -bus_dmamap_create(ring->dma_tag, 0, &ring->spare.dma_map);
	if (err != 0)
		goto err_info;

	for (x = 0; x != size; x++) {
		err = -bus_dmamap_create(ring->dma_tag, 0,
		    &ring->mbuf[x].dma_map);
		if (err != 0) {
			while (x--)
				bus_dmamap_destroy(ring->dma_tag,
				    ring->mbuf[x].dma_map);
			goto err_info;
		}
	}
	en_dbg(DRV, priv, "Allocated MBUF ring at addr:%p size:%d\n",
		 ring->mbuf, tmp);

	err = mlx4_alloc_hwq_res(mdev->dev, &ring->wqres,
				 ring->buf_size, 2 * PAGE_SIZE);
	if (err)
		goto err_dma_map;

	err = mlx4_en_map_buffer(&ring->wqres.buf);
	if (err) {
		en_err(priv, "Failed to map RX buffer\n");
		goto err_hwq;
	}
	ring->buf = ring->wqres.buf.direct.buf;
	*pring = ring;
	return 0;

err_hwq:
	mlx4_free_hwq_res(mdev->dev, &ring->wqres, ring->buf_size);
err_dma_map:
	for (x = 0; x != size; x++) {
		bus_dmamap_destroy(ring->dma_tag,
		    ring->mbuf[x].dma_map);
	}
	bus_dmamap_destroy(ring->dma_tag, ring->spare.dma_map);
err_info:
	vfree(ring->mbuf);
err_dma_tag:
	bus_dma_tag_destroy(ring->dma_tag);
err_ring:
	kfree(ring);
	return (err);
}