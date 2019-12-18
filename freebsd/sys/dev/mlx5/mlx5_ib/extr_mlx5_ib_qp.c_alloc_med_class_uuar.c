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
struct mlx5_uuar_info {scalar_t__* count; } ;

/* Variables and functions */
 int first_hi_uuar (struct mlx5_uuar_info*) ; 
 int first_med_uuar () ; 
 int next_uuar (int) ; 

__attribute__((used)) static int alloc_med_class_uuar(struct mlx5_uuar_info *uuari)
{
	int minidx = first_med_uuar();
	int i;

	for (i = first_med_uuar(); i < first_hi_uuar(uuari); i = next_uuar(i)) {
		if (uuari->count[i] < uuari->count[minidx])
			minidx = i;
	}

	uuari->count[minidx]++;
	return minidx;
}