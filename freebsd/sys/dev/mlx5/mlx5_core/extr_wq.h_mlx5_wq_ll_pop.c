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
struct mlx5_wq_ll {int /*<<< orphan*/  cur_sz; int /*<<< orphan*/ * tail_next; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */

__attribute__((used)) static inline void mlx5_wq_ll_pop(struct mlx5_wq_ll *wq, __be16 ix,
				  __be16 *next_tail_next)
{
	*wq->tail_next = ix;
	wq->tail_next = next_tail_next;
	wq->cur_sz--;
}