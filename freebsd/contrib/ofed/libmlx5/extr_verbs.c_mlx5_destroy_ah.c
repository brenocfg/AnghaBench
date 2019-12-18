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
struct mlx5_ah {scalar_t__ kern_ah; } ;
struct ibv_ah {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct mlx5_ah*) ; 
 int ibv_cmd_destroy_ah (struct ibv_ah*) ; 
 struct mlx5_ah* to_mah (struct ibv_ah*) ; 

int mlx5_destroy_ah(struct ibv_ah *ah)
{
	struct mlx5_ah *mah = to_mah(ah);
	int err;

	if (mah->kern_ah) {
		err = ibv_cmd_destroy_ah(ah);
		if (err)
			return err;
	}

	free(mah);
	return 0;
}