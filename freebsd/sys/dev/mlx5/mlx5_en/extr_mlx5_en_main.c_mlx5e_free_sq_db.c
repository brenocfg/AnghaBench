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
struct mlx5e_sq {TYPE_1__* mbuf; int /*<<< orphan*/  dma_tag; int /*<<< orphan*/  wq; } ;
struct TYPE_2__ {int /*<<< orphan*/  dma_map; int /*<<< orphan*/ * mbuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_MLX5EN ; 
 int /*<<< orphan*/  bus_dmamap_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ *) ; 
 int mlx5_wq_cyc_get_size (int /*<<< orphan*/ *) ; 

void
mlx5e_free_sq_db(struct mlx5e_sq *sq)
{
	int wq_sz = mlx5_wq_cyc_get_size(&sq->wq);
	int x;

	for (x = 0; x != wq_sz; x++) {
		if (sq->mbuf[x].mbuf != NULL) {
			bus_dmamap_unload(sq->dma_tag, sq->mbuf[x].dma_map);
			m_freem(sq->mbuf[x].mbuf);
		}
		bus_dmamap_destroy(sq->dma_tag, sq->mbuf[x].dma_map);
	}
	free(sq->mbuf, M_MLX5EN);
}