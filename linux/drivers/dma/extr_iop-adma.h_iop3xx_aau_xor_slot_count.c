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

__attribute__((used)) static inline int iop3xx_aau_xor_slot_count(size_t len, int src_cnt,
					int *slots_per_op)
{
	static const char slot_count_table[] = {
						1, 1, 1, 1, /* 01 - 04 */
						2, 2, 2, 2, /* 05 - 08 */
						4, 4, 4, 4, /* 09 - 12 */
						4, 4, 4, 4, /* 13 - 16 */
						8, 8, 8, 8, /* 17 - 20 */
						8, 8, 8, 8, /* 21 - 24 */
						8, 8, 8, 8, /* 25 - 28 */
						8, 8, 8, 8, /* 29 - 32 */
					      };
	*slots_per_op = slot_count_table[src_cnt - 1];
	return *slots_per_op;
}