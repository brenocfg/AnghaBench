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
struct fsl_qdma_format {int /*<<< orphan*/  addr_lo; int /*<<< orphan*/  addr_hi; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
qdma_desc_addr_set64(struct fsl_qdma_format *ccdf, u64 addr)
{
	ccdf->addr_hi = upper_32_bits(addr);
	ccdf->addr_lo = cpu_to_le32(lower_32_bits(addr));
}