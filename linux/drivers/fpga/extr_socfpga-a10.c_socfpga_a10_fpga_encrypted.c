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
 int RBF_ENCRYPTION_MODE_OFFSET ; 

__attribute__((used)) static int socfpga_a10_fpga_encrypted(u32 *buf32, size_t buf32_size)
{
	if (buf32_size < RBF_ENCRYPTION_MODE_OFFSET + 1)
		return -EINVAL;

	/* Is the bitstream encrypted? */
	return ((buf32[RBF_ENCRYPTION_MODE_OFFSET] >> 2) & 3) != 0;
}