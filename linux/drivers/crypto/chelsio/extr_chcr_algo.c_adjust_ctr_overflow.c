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
typedef  int u64 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int AES_BLOCK_SIZE ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int adjust_ctr_overflow(u8 *iv, u32 bytes)
{
	__be32 *b = (__be32 *)(iv + AES_BLOCK_SIZE);
	u64 c;
	u32 temp = be32_to_cpu(*--b);

	temp = ~temp;
	c = (u64)temp +  1; // No of block can processed withou overflow
	if ((bytes / AES_BLOCK_SIZE) > c)
		bytes = c * AES_BLOCK_SIZE;
	return bytes;
}