#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  int u32 ;
struct mlx4_icm_table {int virt; int num_icm; int num_obj; int obj_size; int lowmem; int coherent; TYPE_1__** icm; int /*<<< orphan*/  mutex; } ;
struct mlx4_dev {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int ENOMEM ; 
 int GFP_HIGHUSER ; 
 int GFP_KERNEL ; 
 int MLX4_ICM_PAGE_SIZE ; 
 int MLX4_TABLE_CHUNK_SIZE ; 
 unsigned int PAGE_ALIGN (int) ; 
 unsigned int PAGE_SHIFT ; 
 int __GFP_NOWARN ; 
 TYPE_1__** kcalloc (int,int,int) ; 
 int /*<<< orphan*/  kfree (TYPE_1__**) ; 
 scalar_t__ mlx4_MAP_ICM (struct mlx4_dev*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  mlx4_UNMAP_ICM (struct mlx4_dev*,int,int) ; 
 TYPE_1__* mlx4_alloc_icm (struct mlx4_dev*,unsigned int,int,int) ; 
 int /*<<< orphan*/  mlx4_free_icm (struct mlx4_dev*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

int mlx4_init_icm_table(struct mlx4_dev *dev, struct mlx4_icm_table *table,
			u64 virt, int obj_size,	u32 nobj, int reserved,
			int use_lowmem, int use_coherent)
{
	int obj_per_chunk;
	int num_icm;
	unsigned chunk_size;
	int i;
	u64 size;

	obj_per_chunk = MLX4_TABLE_CHUNK_SIZE / obj_size;
	num_icm = (nobj + obj_per_chunk - 1) / obj_per_chunk;

	table->icm      = kcalloc(num_icm, sizeof *table->icm, GFP_KERNEL);
	if (!table->icm)
		return -ENOMEM;
	table->virt     = virt;
	table->num_icm  = num_icm;
	table->num_obj  = nobj;
	table->obj_size = obj_size;
	table->lowmem   = use_lowmem;
	table->coherent = use_coherent;
	mutex_init(&table->mutex);

	size = (u64) nobj * obj_size;
	for (i = 0; i * MLX4_TABLE_CHUNK_SIZE < reserved * obj_size; ++i) {
		chunk_size = MLX4_TABLE_CHUNK_SIZE;
		if ((u64) (i + 1) * MLX4_TABLE_CHUNK_SIZE > size)
			chunk_size = PAGE_ALIGN(size -
					i * MLX4_TABLE_CHUNK_SIZE);

		table->icm[i] = mlx4_alloc_icm(dev, chunk_size >> PAGE_SHIFT,
					       (use_lowmem ? GFP_KERNEL : GFP_HIGHUSER) |
					       __GFP_NOWARN, use_coherent);
		if (!table->icm[i])
			goto err;
		if (mlx4_MAP_ICM(dev, table->icm[i], virt + i * MLX4_TABLE_CHUNK_SIZE)) {
			mlx4_free_icm(dev, table->icm[i], use_coherent);
			table->icm[i] = NULL;
			goto err;
		}

		/*
		 * Add a reference to this ICM chunk so that it never
		 * gets freed (since it contains reserved firmware objects).
		 */
		++table->icm[i]->refcount;
	}

	return 0;

err:
	for (i = 0; i < num_icm; ++i)
		if (table->icm[i]) {
			mlx4_UNMAP_ICM(dev, virt + i * MLX4_TABLE_CHUNK_SIZE,
				       MLX4_TABLE_CHUNK_SIZE / MLX4_ICM_PAGE_SIZE);
			mlx4_free_icm(dev, table->icm[i], use_coherent);
		}

	kfree(table->icm);

	return -ENOMEM;
}