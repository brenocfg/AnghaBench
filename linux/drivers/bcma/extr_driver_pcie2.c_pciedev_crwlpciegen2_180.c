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
struct bcma_drv_pcie2 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCMA_CORE_PCIE2_CONFIGINDADDR ; 
 int /*<<< orphan*/  BCMA_CORE_PCIE2_CONFIGINDDATA ; 
 int /*<<< orphan*/  PCIE2_PMCR_REFUP ; 
 int /*<<< orphan*/  pcie2_set32 (struct bcma_drv_pcie2*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pcie2_write32 (struct bcma_drv_pcie2*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pciedev_crwlpciegen2_180(struct bcma_drv_pcie2 *pcie2)
{
	pcie2_write32(pcie2, BCMA_CORE_PCIE2_CONFIGINDADDR, PCIE2_PMCR_REFUP);
	pcie2_set32(pcie2, BCMA_CORE_PCIE2_CONFIGINDDATA, 0x1f);
}