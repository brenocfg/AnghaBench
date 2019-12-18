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
struct ibv_cq_ex {int dummy; } ;

/* Variables and functions */
 int mlx5_next_poll (struct ibv_cq_ex*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline int mlx5_next_poll_v1(struct ibv_cq_ex *ibcq)
{
	return mlx5_next_poll(ibcq, 0, 1);
}