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
struct clk_pllv4 {scalar_t__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOCK_TIMEOUT_US ; 
 scalar_t__ PLL_CSR_OFFSET ; 
 int PLL_VLD ; 
 int readl_poll_timeout (scalar_t__,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int clk_pllv4_wait_lock(struct clk_pllv4 *pll)
{
	u32 csr;

	return readl_poll_timeout(pll->base  + PLL_CSR_OFFSET,
				  csr, csr & PLL_VLD, 0, LOCK_TIMEOUT_US);
}