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
typedef  scalar_t__ u16 ;
struct TYPE_2__ {scalar_t__ sz_m1; } ;
struct mlx5e_sq {scalar_t__ cc; scalar_t__ pc; TYPE_1__ wq; } ;

/* Variables and functions */

__attribute__((used)) static inline bool
mlx5e_sq_has_room_for(struct mlx5e_sq *sq, u16 n)
{
	u16 cc = sq->cc;
	u16 pc = sq->pc;

	return ((sq->wq.sz_m1 & (cc - pc)) >= n || cc == pc);
}