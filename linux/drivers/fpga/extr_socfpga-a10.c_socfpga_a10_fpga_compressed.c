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
 int EINVAL ; 
 int RBF_DECOMPRESS_OFFSET ; 

__attribute__((used)) static int socfpga_a10_fpga_compressed(u32 *buf32, size_t buf32_size)
{
	if (buf32_size < RBF_DECOMPRESS_OFFSET + 1)
		return -EINVAL;

	/* Is the bitstream compressed? */
	return !((buf32[RBF_DECOMPRESS_OFFSET] >> 1) & 1);
}