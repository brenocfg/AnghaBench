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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crc_itu_t (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

int fw_compute_block_crc(__be32 *block)
{
	int length;
	u16 crc;

	length = (be32_to_cpu(block[0]) >> 16) & 0xff;
	crc = crc_itu_t(0, (u8 *)&block[1], length * 4);
	*block |= cpu_to_be32(crc);

	return length;
}