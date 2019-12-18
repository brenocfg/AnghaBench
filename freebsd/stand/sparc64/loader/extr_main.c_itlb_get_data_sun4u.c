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
typedef  int u_long ;
typedef  int /*<<< orphan*/  u_int ;

/* Variables and functions */
 int /*<<< orphan*/  ASI_ITLB_DATA_ACCESS_REG ; 
 int PSTATE_IE ; 
 int /*<<< orphan*/  TLB_DAR_SLOT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ldxa (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rdpr (int) ; 
 int /*<<< orphan*/  wrpr (int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u_long
itlb_get_data_sun4u(u_int tlb, u_int slot)
{
	u_long data, pstate;

	slot = TLB_DAR_SLOT(tlb, slot);
	/*
	 * We read ASI_DTLB_DATA_ACCESS_REG twice back-to-back in order to
	 * work around errata of USIII and beyond.
	 */
	pstate = rdpr(pstate);
	wrpr(pstate, pstate & ~PSTATE_IE, 0);
	(void)ldxa(slot, ASI_ITLB_DATA_ACCESS_REG);
	data = ldxa(slot, ASI_ITLB_DATA_ACCESS_REG);
	wrpr(pstate, pstate, 0);
	return (data);
}