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
struct mlx5e_sq {TYPE_1__* mbuf; int /*<<< orphan*/  dma_tag; int /*<<< orphan*/  wq; } ;
struct TYPE_3__ {int /*<<< orphan*/  dma_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_MLX5EN ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int bus_dmamap_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamap_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* malloc (int,int /*<<< orphan*/ ,int) ; 
 int mlx5_wq_cyc_get_size (int /*<<< orphan*/ *) ; 

int
mlx5e_alloc_sq_db(struct mlx5e_sq *sq)
{
	int wq_sz = mlx5_wq_cyc_get_size(&sq->wq);
	int err;
	int x;

	sq->mbuf = malloc(wq_sz * sizeof(sq->mbuf[0]), M_MLX5EN, M_WAITOK | M_ZERO);

	/* Create DMA descriptor MAPs */
	for (x = 0; x != wq_sz; x++) {
		err = -bus_dmamap_create(sq->dma_tag, 0, &sq->mbuf[x].dma_map);
		if (err != 0) {
			while (x--)
				bus_dmamap_destroy(sq->dma_tag, sq->mbuf[x].dma_map);
			free(sq->mbuf, M_MLX5EN);
			return (err);
		}
	}
	return (0);
}