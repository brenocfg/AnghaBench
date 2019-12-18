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
struct mlx5_ah {int dummy; } ;
struct ibv_ah {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ah ; 
 struct mlx5_ah* to_mxxx (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct mlx5_ah *to_mah(struct ibv_ah *ibah)
{
	return to_mxxx(ah, ah);
}