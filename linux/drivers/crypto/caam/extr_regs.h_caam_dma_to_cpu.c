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
 int /*<<< orphan*/  CONFIG_ARCH_DMA_ADDR_T_64BIT ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  caam32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  caam_dma64_to_cpu (int /*<<< orphan*/ ) ; 
 int caam_ptr_sz ; 

__attribute__((used)) static inline u64 caam_dma_to_cpu(u64 value)
{
	if (IS_ENABLED(CONFIG_ARCH_DMA_ADDR_T_64BIT) &&
	    caam_ptr_sz == sizeof(u64))
		return caam_dma64_to_cpu(value);
	else
		return caam32_to_cpu(value);
}