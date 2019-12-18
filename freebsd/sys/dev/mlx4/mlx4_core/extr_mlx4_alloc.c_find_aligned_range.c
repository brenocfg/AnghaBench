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
 scalar_t__ test_bit (unsigned long,unsigned long*) ; 

__attribute__((used)) static unsigned long find_aligned_range(unsigned long *bitmap,
					u32 start, u32 nbits,
					int len, int align, u32 skip_mask)
{
	unsigned long end, i;

again:
	start = ALIGN(start, align);

	while ((start < nbits) && (test_bit(start, bitmap) ||
				   (start & skip_mask)))
		start += align;

	if (start >= nbits)
		return -1;

	end = start+len;
	if (end > nbits)
		return -1;

	for (i = start + 1; i < end; i++) {
		if (test_bit(i, bitmap) || ((u32)i & skip_mask)) {
			start = i + 1;
			goto again;
		}
	}

	return start;
}