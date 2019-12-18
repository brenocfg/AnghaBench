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
struct TYPE_2__ {scalar_t__ d64; int /*<<< orphan*/  d32; } ;
struct mlx5e_sq {scalar_t__ cev_counter; TYPE_1__ doorbell; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_thread_fence_rel () ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  mlx5e_send_nop (struct mlx5e_sq*,int) ; 
 int /*<<< orphan*/  mlx5e_sq_has_room_for (struct mlx5e_sq*,int) ; 
 int /*<<< orphan*/  mlx5e_tx_notify_hw (struct mlx5e_sq*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mlx5e_sq_send_nops_locked(struct mlx5e_sq *sq, int can_sleep)
{
	/* fill up remainder with NOPs */
	while (sq->cev_counter != 0) {
		while (!mlx5e_sq_has_room_for(sq, 1)) {
			if (can_sleep != 0) {
				mtx_unlock(&sq->lock);
				msleep(4);
				mtx_lock(&sq->lock);
			} else {
				goto done;
			}
		}
		/* send a single NOP */
		mlx5e_send_nop(sq, 1);
		atomic_thread_fence_rel();
	}
done:
	/* Check if we need to write the doorbell */
	if (likely(sq->doorbell.d64 != 0)) {
		mlx5e_tx_notify_hw(sq, sq->doorbell.d32, 0);
		sq->doorbell.d64 = 0;
	}
}