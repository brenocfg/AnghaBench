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
struct hw_perf_event {int /*<<< orphan*/  iommu_cntr; int /*<<< orphan*/  iommu_bank; } ;
struct perf_event {struct hw_perf_event hw; } ;
struct amd_iommu {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 int GET_CSOURCE (struct hw_perf_event*) ; 
 int GET_DEVID (struct hw_perf_event*) ; 
 int GET_DEVID_MASK (struct hw_perf_event*) ; 
 int GET_DOMID (struct hw_perf_event*) ; 
 int GET_DOMID_MASK (struct hw_perf_event*) ; 
 int GET_PASID (struct hw_perf_event*) ; 
 int GET_PASID_MASK (struct hw_perf_event*) ; 
 int /*<<< orphan*/  IOMMU_PC_COUNTER_SRC_REG ; 
 int /*<<< orphan*/  IOMMU_PC_DEVID_MATCH_REG ; 
 int /*<<< orphan*/  IOMMU_PC_DOMID_MATCH_REG ; 
 int /*<<< orphan*/  IOMMU_PC_PASID_MATCH_REG ; 
 int /*<<< orphan*/  amd_iommu_pc_set_reg (struct amd_iommu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 struct amd_iommu* perf_event_2_iommu (struct perf_event*) ; 

__attribute__((used)) static void perf_iommu_enable_event(struct perf_event *ev)
{
	struct amd_iommu *iommu = perf_event_2_iommu(ev);
	struct hw_perf_event *hwc = &ev->hw;
	u8 bank = hwc->iommu_bank;
	u8 cntr = hwc->iommu_cntr;
	u64 reg = 0ULL;

	reg = GET_CSOURCE(hwc);
	amd_iommu_pc_set_reg(iommu, bank, cntr, IOMMU_PC_COUNTER_SRC_REG, &reg);

	reg = GET_DEVID_MASK(hwc);
	reg = GET_DEVID(hwc) | (reg << 32);
	if (reg)
		reg |= BIT(31);
	amd_iommu_pc_set_reg(iommu, bank, cntr, IOMMU_PC_DEVID_MATCH_REG, &reg);

	reg = GET_PASID_MASK(hwc);
	reg = GET_PASID(hwc) | (reg << 32);
	if (reg)
		reg |= BIT(31);
	amd_iommu_pc_set_reg(iommu, bank, cntr, IOMMU_PC_PASID_MATCH_REG, &reg);

	reg = GET_DOMID_MASK(hwc);
	reg = GET_DOMID(hwc) | (reg << 32);
	if (reg)
		reg |= BIT(31);
	amd_iommu_pc_set_reg(iommu, bank, cntr, IOMMU_PC_DOMID_MATCH_REG, &reg);
}