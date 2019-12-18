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
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 scalar_t__ caam_imx ; 
 scalar_t__ cpu_to_caam32 (int /*<<< orphan*/ ) ; 
 int cpu_to_caam64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u64 cpu_to_caam_dma64(dma_addr_t value)
{
	if (caam_imx)
		return (((u64)cpu_to_caam32(lower_32_bits(value)) << 32) |
			 (u64)cpu_to_caam32(upper_32_bits(value)));

	return cpu_to_caam64(value);
}