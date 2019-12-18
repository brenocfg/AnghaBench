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
typedef  int /*<<< orphan*/  uint32_t ;
struct mlx5_cq {TYPE_1__* cqe64; } ;
struct ibv_cq_ex {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  slid; } ;

/* Variables and functions */
 int /*<<< orphan*/  be16toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibv_cq_ex_to_cq (struct ibv_cq_ex*) ; 
 struct mlx5_cq* to_mcq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline uint32_t mlx5_cq_read_wc_slid(struct ibv_cq_ex *ibcq)
{
	struct mlx5_cq *cq = to_mcq(ibv_cq_ex_to_cq(ibcq));

	return (uint32_t)be16toh(cq->cqe64->slid);
}