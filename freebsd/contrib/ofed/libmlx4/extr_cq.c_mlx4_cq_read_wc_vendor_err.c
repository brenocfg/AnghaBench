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
typedef  int /*<<< orphan*/  uint32_t ;
struct mlx4_err_cqe {int /*<<< orphan*/  vendor_err; } ;
struct mlx4_cq {scalar_t__ cqe; } ;
struct ibv_cq_ex {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ibv_cq_ex_to_cq (struct ibv_cq_ex*) ; 
 struct mlx4_cq* to_mcq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t mlx4_cq_read_wc_vendor_err(struct ibv_cq_ex *ibcq)
{
	struct mlx4_cq *cq = to_mcq(ibv_cq_ex_to_cq(ibcq));
	struct mlx4_err_cqe *ecqe = (struct mlx4_err_cqe *)cq->cqe;

	return ecqe->vendor_err;
}