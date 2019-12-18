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
typedef  int uint8_t ;
struct mlx5_cq {TYPE_1__* cqe64; } ;
struct ibv_cq_ex {int dummy; } ;
struct TYPE_2__ {int ml_path; } ;

/* Variables and functions */
 int /*<<< orphan*/  ibv_cq_ex_to_cq (struct ibv_cq_ex*) ; 
 struct mlx5_cq* to_mcq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline uint8_t mlx5_cq_read_wc_dlid_path_bits(struct ibv_cq_ex *ibcq)
{
	struct mlx5_cq *cq = to_mcq(ibv_cq_ex_to_cq(ibcq));

	return cq->cqe64->ml_path & 0x7f;
}