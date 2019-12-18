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
 int /*<<< orphan*/  _mlx5_end_poll (struct ibv_cq_ex*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void mlx5_end_poll_lock(struct ibv_cq_ex *ibcq)
{
	_mlx5_end_poll(ibcq, 1, 0);
}