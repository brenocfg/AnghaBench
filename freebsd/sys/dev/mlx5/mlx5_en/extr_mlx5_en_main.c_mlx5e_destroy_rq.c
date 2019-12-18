#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  ctx; } ;
struct mlx5e_rq {int /*<<< orphan*/  dma_tag; int /*<<< orphan*/  wq_ctrl; TYPE_2__* mbuf; int /*<<< orphan*/  wq; int /*<<< orphan*/  lro; TYPE_1__ stats; } ;
struct TYPE_4__ {int /*<<< orphan*/  dma_map; int /*<<< orphan*/ * mbuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_MLX5EN ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_wq_destroy (int /*<<< orphan*/ *) ; 
 int mlx5_wq_ll_get_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysctl_ctx_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcp_lro_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mlx5e_destroy_rq(struct mlx5e_rq *rq)
{
	int wq_sz;
	int i;

	/* destroy all sysctl nodes */
	sysctl_ctx_free(&rq->stats.ctx);

	/* free leftover LRO packets, if any */
	tcp_lro_free(&rq->lro);

	wq_sz = mlx5_wq_ll_get_size(&rq->wq);
	for (i = 0; i != wq_sz; i++) {
		if (rq->mbuf[i].mbuf != NULL) {
			bus_dmamap_unload(rq->dma_tag, rq->mbuf[i].dma_map);
			m_freem(rq->mbuf[i].mbuf);
		}
		bus_dmamap_destroy(rq->dma_tag, rq->mbuf[i].dma_map);
	}
	free(rq->mbuf, M_MLX5EN);
	mlx5_wq_destroy(&rq->wq_ctrl);
	bus_dma_tag_destroy(rq->dma_tag);
}