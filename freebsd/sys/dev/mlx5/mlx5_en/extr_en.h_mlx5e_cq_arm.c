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
struct TYPE_4__ {int /*<<< orphan*/  cc; } ;
struct mlx5_core_cq {TYPE_1__* uar; } ;
struct mlx5e_cq {TYPE_2__ wq; struct mlx5_core_cq mcq; } ;
typedef  int /*<<< orphan*/  spinlock_t ;
struct TYPE_3__ {int /*<<< orphan*/  map; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_CQ_DB_REQ_NOT ; 
 int /*<<< orphan*/  mlx5_cq_arm (struct mlx5_core_cq*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
mlx5e_cq_arm(struct mlx5e_cq *cq, spinlock_t *dblock)
{
	struct mlx5_core_cq *mcq;

	mcq = &cq->mcq;
	mlx5_cq_arm(mcq, MLX5_CQ_DB_REQ_NOT, mcq->uar->map, dblock, cq->wq.cc);
}