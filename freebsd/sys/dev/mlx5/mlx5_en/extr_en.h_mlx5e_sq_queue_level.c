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
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_2__ {int sz_m1; } ;
struct mlx5e_sq {int cc; int pc; TYPE_1__ wq; } ;

/* Variables and functions */
 int IF_SND_QUEUE_LEVEL_MAX ; 

__attribute__((used)) static inline u32
mlx5e_sq_queue_level(struct mlx5e_sq *sq)
{
	u16 cc;
	u16 pc;

	if (sq == NULL)
		return (0);

	cc = sq->cc;
	pc = sq->pc;

	return (((sq->wq.sz_m1 & (pc - cc)) *
	    IF_SND_QUEUE_LEVEL_MAX) / sq->wq.sz_m1);
}