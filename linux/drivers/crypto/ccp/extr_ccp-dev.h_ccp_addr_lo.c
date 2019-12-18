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
struct ccp_dma_info {scalar_t__ offset; scalar_t__ address; } ;

/* Variables and functions */
 int /*<<< orphan*/  lower_32_bits (scalar_t__) ; 

__attribute__((used)) static inline u32 ccp_addr_lo(struct ccp_dma_info *info)
{
	return lower_32_bits(info->address + info->offset);
}