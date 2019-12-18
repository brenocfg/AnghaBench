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
struct mlx4_cqe {int dummy; } ;
struct mlx4_cq {int /*<<< orphan*/  cur_qp; } ;

/* Variables and functions */
 int mlx4_parse_cqe (struct mlx4_cq*,struct mlx4_cqe*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline int mlx4_parse_lazy_cqe(struct mlx4_cq *cq,
				      struct mlx4_cqe *cqe)
{
	return mlx4_parse_cqe(cq, cqe, &cq->cur_qp, NULL, 1);
}