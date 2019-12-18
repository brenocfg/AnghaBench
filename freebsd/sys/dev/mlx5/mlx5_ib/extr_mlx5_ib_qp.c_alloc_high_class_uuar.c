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
struct mlx5_uuar_info {int /*<<< orphan*/ * count; int /*<<< orphan*/  bitmap; } ;

/* Variables and functions */
 int ENOMEM ; 
 int first_hi_uuar (struct mlx5_uuar_info*) ; 
 int max_uuari (struct mlx5_uuar_info*) ; 
 int next_uuar (int) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int alloc_high_class_uuar(struct mlx5_uuar_info *uuari)
{
	int i;

	for (i = first_hi_uuar(uuari); i < max_uuari(uuari); i = next_uuar(i)) {
		if (!test_bit(i, uuari->bitmap)) {
			set_bit(i, uuari->bitmap);
			uuari->count[i]++;
			return i;
		}
	}

	return -ENOMEM;
}