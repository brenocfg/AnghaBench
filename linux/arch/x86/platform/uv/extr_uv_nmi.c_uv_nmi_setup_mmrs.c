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

/* Variables and functions */
 int /*<<< orphan*/  UVH_NMI_MMR ; 
 int /*<<< orphan*/  UVH_NMI_MMRX ; 
 int /*<<< orphan*/  UVH_NMI_MMRX_CLEAR ; 
 int /*<<< orphan*/  UVH_NMI_MMRX_REQ ; 
 unsigned long UVH_NMI_MMRX_REQ_SHIFT ; 
 unsigned long UVH_NMI_MMRX_SHIFT ; 
 int /*<<< orphan*/  UVH_NMI_MMRX_SUPPORTED ; 
 int /*<<< orphan*/  UVH_NMI_MMRX_TYPE ; 
 int /*<<< orphan*/  UVH_NMI_MMR_CLEAR ; 
 unsigned long UVH_NMI_MMR_SHIFT ; 
 int /*<<< orphan*/  UVH_NMI_MMR_TYPE ; 
 int /*<<< orphan*/  nmi_mmr ; 
 int /*<<< orphan*/  nmi_mmr_clear ; 
 unsigned long nmi_mmr_pending ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ uv_read_local_mmr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv_write_local_mmr (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void uv_nmi_setup_mmrs(void)
{
	if (uv_read_local_mmr(UVH_NMI_MMRX_SUPPORTED)) {
		uv_write_local_mmr(UVH_NMI_MMRX_REQ,
					1UL << UVH_NMI_MMRX_REQ_SHIFT);
		nmi_mmr = UVH_NMI_MMRX;
		nmi_mmr_clear = UVH_NMI_MMRX_CLEAR;
		nmi_mmr_pending = 1UL << UVH_NMI_MMRX_SHIFT;
		pr_info("UV: SMI NMI support: %s\n", UVH_NMI_MMRX_TYPE);
	} else {
		nmi_mmr = UVH_NMI_MMR;
		nmi_mmr_clear = UVH_NMI_MMR_CLEAR;
		nmi_mmr_pending = 1UL << UVH_NMI_MMR_SHIFT;
		pr_info("UV: SMI NMI support: %s\n", UVH_NMI_MMR_TYPE);
	}
}