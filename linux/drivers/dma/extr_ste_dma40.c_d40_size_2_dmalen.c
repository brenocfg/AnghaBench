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
typedef  int u32 ;

/* Variables and functions */
 int ALIGN (int,int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  IS_ALIGNED (int,int) ; 
 int STEDMA40_MAX_SEG_SIZE ; 
 int max (int,int) ; 
 int min (int,int) ; 

__attribute__((used)) static int d40_size_2_dmalen(int size, u32 data_width1, u32 data_width2)
{
	int dmalen;
	u32 max_w = max(data_width1, data_width2);
	u32 min_w = min(data_width1, data_width2);
	u32 seg_max = ALIGN(STEDMA40_MAX_SEG_SIZE * min_w, max_w);

	if (seg_max > STEDMA40_MAX_SEG_SIZE)
		seg_max -= max_w;

	if (!IS_ALIGNED(size, max_w))
		return -EINVAL;

	if (size <= seg_max)
		dmalen = 1;
	else {
		dmalen = size / seg_max;
		if (dmalen * seg_max < size)
			dmalen++;
	}
	return dmalen;
}