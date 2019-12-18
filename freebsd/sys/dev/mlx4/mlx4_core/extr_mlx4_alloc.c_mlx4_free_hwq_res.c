#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct mlx4_hwq_resources {int /*<<< orphan*/  db; int /*<<< orphan*/  buf; int /*<<< orphan*/  mtt; } ;
struct mlx4_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx4_buf_free (struct mlx4_dev*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx4_db_free (struct mlx4_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx4_mtt_cleanup (struct mlx4_dev*,int /*<<< orphan*/ *) ; 

void mlx4_free_hwq_res(struct mlx4_dev *dev, struct mlx4_hwq_resources *wqres,
		       int size)
{
	mlx4_mtt_cleanup(dev, &wqres->mtt);
	mlx4_buf_free(dev, size, &wqres->buf);
	mlx4_db_free(dev, &wqres->db);
}