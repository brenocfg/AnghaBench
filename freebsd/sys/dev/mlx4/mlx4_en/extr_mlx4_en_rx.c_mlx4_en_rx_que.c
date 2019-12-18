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
struct thread {int dummy; } ;
struct mlx4_en_cq {TYPE_1__* dev; int /*<<< orphan*/  curr_poll_rx_cpu_id; } ;
struct TYPE_2__ {int /*<<< orphan*/  if_softc; } ;

/* Variables and functions */
 scalar_t__ MLX4_EN_RX_BUDGET ; 
 struct thread* curthread ; 
 int /*<<< orphan*/  mlx4_en_arm_cq (int /*<<< orphan*/ ,struct mlx4_en_cq*) ; 
 scalar_t__ mlx4_en_poll_rx_cq (struct mlx4_en_cq*,scalar_t__) ; 
 int /*<<< orphan*/  sched_bind (struct thread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_lock (struct thread*) ; 
 int /*<<< orphan*/  thread_unlock (struct thread*) ; 

void mlx4_en_rx_que(void *context, int pending)
{
        struct mlx4_en_cq *cq;
	struct thread *td;

        cq = context;
	td = curthread;

	thread_lock(td);
	sched_bind(td, cq->curr_poll_rx_cpu_id);
	thread_unlock(td);

        while (mlx4_en_poll_rx_cq(cq, MLX4_EN_RX_BUDGET)
                        == MLX4_EN_RX_BUDGET);
        mlx4_en_arm_cq(cq->dev->if_softc, cq);
}