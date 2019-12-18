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
struct mlx5_cqe64 {int dummy; } ;
struct mlx5_cq {int /*<<< orphan*/  cur_srq; int /*<<< orphan*/  cur_rsc; } ;

/* Variables and functions */
 int mlx5_parse_cqe (struct mlx5_cq*,struct mlx5_cqe64*,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static inline int mlx5_parse_lazy_cqe(struct mlx5_cq *cq,
				      struct mlx5_cqe64 *cqe64,
				      void *cqe, int cqe_ver)
{
	return mlx5_parse_cqe(cq, cqe64, cqe, &cq->cur_rsc, &cq->cur_srq, NULL, cqe_ver, 1);
}