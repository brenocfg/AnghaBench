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
typedef  int /*<<< orphan*/  uint32_t ;
struct bcm_platform {int /*<<< orphan*/  cc_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCM_SOC_ADDR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHIPC_CHIPST ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t
bcm_pmu_read_chipst(void *ctx)
{
	struct bcm_platform *bp = ctx;
	return (readl(BCM_SOC_ADDR(bp->cc_addr, CHIPC_CHIPST)));
}