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
struct mlx5e_sq {scalar_t__ cev_counter; scalar_t__ cev_factor; } ;

/* Variables and functions */

__attribute__((used)) static inline bool
mlx5e_do_send_cqe(struct mlx5e_sq *sq)
{
	sq->cev_counter++;
	/* interleave the CQEs */
	if (sq->cev_counter >= sq->cev_factor) {
		sq->cev_counter = 0;
		return (1);
	}
	return (0);
}