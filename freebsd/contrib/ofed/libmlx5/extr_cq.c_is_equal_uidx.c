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
typedef  int uint32_t ;
struct mlx5_cqe64 {int /*<<< orphan*/  srqn_uidx; } ;

/* Variables and functions */
 int be32toh (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int is_equal_uidx(struct mlx5_cqe64 *cqe64, uint32_t uidx)
{
	return uidx == (be32toh(cqe64->srqn_uidx) & 0xffffff);
}