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
struct mlx5_db_pgdir {int /*<<< orphan*/  db_page; TYPE_1__* fw_page; int /*<<< orphan*/  db_dma; int /*<<< orphan*/  bitmap; } ;
struct mlx5_core_dev {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  dma_addr; int /*<<< orphan*/  virt_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MLX5_ADAPTER_PAGE_SIZE ; 
 int /*<<< orphan*/  MLX5_DB_PER_PAGE ; 
 int /*<<< orphan*/  bitmap_fill (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mlx5_db_pgdir*) ; 
 struct mlx5_db_pgdir* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* mlx5_fwp_alloc (struct mlx5_core_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlx5_fwp_flush (TYPE_1__*) ; 

__attribute__((used)) static struct mlx5_db_pgdir *mlx5_alloc_db_pgdir(struct mlx5_core_dev *dev,
						 int node)
{
	struct mlx5_db_pgdir *pgdir;

	pgdir = kzalloc(sizeof(*pgdir), GFP_KERNEL);

	bitmap_fill(pgdir->bitmap, MLX5_DB_PER_PAGE);

	pgdir->fw_page = mlx5_fwp_alloc(dev, GFP_KERNEL, 1);
	if (pgdir->fw_page != NULL) {
		pgdir->db_page = pgdir->fw_page->virt_addr;
		pgdir->db_dma = pgdir->fw_page->dma_addr;

		/* clean allocated memory */
		memset(pgdir->db_page, 0, MLX5_ADAPTER_PAGE_SIZE);

		/* flush memory to RAM */
		mlx5_fwp_flush(pgdir->fw_page);
	}
	if (!pgdir->db_page) {
		kfree(pgdir);
		return NULL;
	}

	return pgdir;
}