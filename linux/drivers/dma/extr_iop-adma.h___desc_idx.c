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

/* Variables and functions */

__attribute__((used)) static inline int __desc_idx(int src_idx)
{
	static const int desc_idx_table[] = { 0, 0, 0, 0,
					      0, 1, 2, 3,
					      5, 6, 7, 8,
					      9, 10, 11, 12,
					      14, 15, 16, 17,
					      18, 19, 20, 21,
					      23, 24, 25, 26,
					      27, 28, 29, 30,
					    };

	return desc_idx_table[src_idx];
}