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
typedef  int u64 ;

/* Variables and functions */

__attribute__((used)) static u64 skx_do_interleave(u64 addr, int shift, int ways, u64 lowbits)
{
	addr >>= shift;
	addr /= ways;
	addr <<= shift;

	return addr | (lowbits & ((1ull << shift) - 1));
}