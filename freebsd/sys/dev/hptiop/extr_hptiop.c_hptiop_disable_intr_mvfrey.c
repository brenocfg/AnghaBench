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
 int /*<<< orphan*/  BUS_SPACE_RD4_MVFREY2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUS_SPACE_WRT4_MVFREY2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f0_doorbell_enable ; 
 int /*<<< orphan*/  isr_enable ; 
 int /*<<< orphan*/  pcie_f0_int_enable ; 

__attribute__((used)) static void hptiop_disable_intr_mvfrey(struct hpt_iop_hba *hba)
{
	BUS_SPACE_WRT4_MVFREY2(f0_doorbell_enable, 0);
	BUS_SPACE_RD4_MVFREY2(f0_doorbell_enable);

	BUS_SPACE_WRT4_MVFREY2(isr_enable, 0);
	BUS_SPACE_RD4_MVFREY2(isr_enable);

	BUS_SPACE_WRT4_MVFREY2(pcie_f0_int_enable, 0);
	BUS_SPACE_RD4_MVFREY2(pcie_f0_int_enable);
}