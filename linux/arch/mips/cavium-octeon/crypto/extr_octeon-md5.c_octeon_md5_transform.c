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
typedef  int /*<<< orphan*/  u64 ;

/* Variables and functions */
 int /*<<< orphan*/  octeon_md5_start (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  write_octeon_64bit_block_dword (int /*<<< orphan*/  const,int) ; 

__attribute__((used)) static void octeon_md5_transform(const void *_block)
{
	const u64 *block = _block;

	write_octeon_64bit_block_dword(block[0], 0);
	write_octeon_64bit_block_dword(block[1], 1);
	write_octeon_64bit_block_dword(block[2], 2);
	write_octeon_64bit_block_dword(block[3], 3);
	write_octeon_64bit_block_dword(block[4], 4);
	write_octeon_64bit_block_dword(block[5], 5);
	write_octeon_64bit_block_dword(block[6], 6);
	octeon_md5_start(block[7]);
}