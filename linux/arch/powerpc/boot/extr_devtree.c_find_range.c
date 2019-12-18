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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int MAX_ADDR_CELLS ; 
 scalar_t__ compare_reg (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  copy_val (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int find_range(u32 *reg, u32 *ranges, int nregaddr,
                      int naddr, int nsize, int buflen)
{
	int nrange = nregaddr + naddr + nsize;
	int i;

	for (i = 0; i + nrange <= buflen; i += nrange) {
		u32 range_addr[MAX_ADDR_CELLS];
		u32 range_size[MAX_ADDR_CELLS];

		copy_val(range_addr, ranges + i, nregaddr);
		copy_val(range_size, ranges + i + nregaddr + naddr, nsize);

		if (compare_reg(reg, range_addr, range_size))
			return i;
	}

	return -1;
}