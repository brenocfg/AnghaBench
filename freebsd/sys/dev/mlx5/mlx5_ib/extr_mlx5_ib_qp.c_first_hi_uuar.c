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
struct mlx5_uuar_info {int dummy; } ;

/* Variables and functions */
 int first_med_uuar () ; 
 int next_uuar (int) ; 
 int num_med_uuar (struct mlx5_uuar_info*) ; 

__attribute__((used)) static int first_hi_uuar(struct mlx5_uuar_info *uuari)
{
	int med;
	int i;
	int t;

	med = num_med_uuar(uuari);
	for (t = 0, i = first_med_uuar();; i = next_uuar(i)) {
		t++;
		if (t == med)
			return next_uuar(i);
	}

	return 0;
}