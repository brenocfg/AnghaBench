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
typedef  int /*<<< orphan*/  uint8_t ;
struct mlx5_rwqe_sig {int /*<<< orphan*/  signature; } ;
typedef  struct mlx5_rwqe_sig uint32_t ;
typedef  struct mlx5_rwqe_sig uint16_t ;
struct TYPE_2__ {struct mlx5_rwqe_sig wq_num; } ;
struct mlx5_rwq {TYPE_1__ wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  calc_sig (struct mlx5_rwqe_sig*,int) ; 

__attribute__((used)) static void set_wq_sig_seg(struct mlx5_rwq *rwq, struct mlx5_rwqe_sig *sig,
			   int size, uint16_t idx)
{
	uint8_t  sign;
	uint32_t qpn = rwq->wq.wq_num;

	sign = calc_sig(sig, size);
	sign ^= calc_sig(&qpn, 4);
	sign ^= calc_sig(&idx, 2);
	sig->signature = sign;
}