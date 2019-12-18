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
struct mlx5_db_pgdir {scalar_t__ db_dma; scalar_t__* db_page; int /*<<< orphan*/  bitmap; } ;
struct TYPE_2__ {struct mlx5_db_pgdir* pgdir; } ;
struct mlx5_db {int index; scalar_t__* db; scalar_t__ dma; TYPE_1__ u; } ;

/* Variables and functions */
 int ENOMEM ; 
 int L1_CACHE_BYTES ; 
 int MLX5_DB_PER_PAGE ; 
 int /*<<< orphan*/  __clear_bit (int,int /*<<< orphan*/ ) ; 
 int find_first_bit (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mlx5_alloc_db_from_pgdir(struct mlx5_db_pgdir *pgdir,
				    struct mlx5_db *db)
{
	int offset;
	int i;

	i = find_first_bit(pgdir->bitmap, MLX5_DB_PER_PAGE);
	if (i >= MLX5_DB_PER_PAGE)
		return -ENOMEM;

	__clear_bit(i, pgdir->bitmap);

	db->u.pgdir = pgdir;
	db->index   = i;
	offset = db->index * L1_CACHE_BYTES;
	db->db      = pgdir->db_page + offset / sizeof(*pgdir->db_page);
	db->dma     = pgdir->db_dma  + offset;

	db->db[0] = 0;
	db->db[1] = 0;

	return 0;
}