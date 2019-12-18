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
struct hpt_iop_hba {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_SPACE_WRT4_ITL (int /*<<< orphan*/ ,int) ; 
 int IOPMU_OUTBOUND_INT_MSG0 ; 
 int IOPMU_OUTBOUND_INT_POSTQUEUE ; 
 int /*<<< orphan*/  outbound_intmask ; 

__attribute__((used)) static void hptiop_enable_intr_itl(struct hpt_iop_hba *hba)
{
	BUS_SPACE_WRT4_ITL(outbound_intmask,
		~(IOPMU_OUTBOUND_INT_POSTQUEUE | IOPMU_OUTBOUND_INT_MSG0));
}