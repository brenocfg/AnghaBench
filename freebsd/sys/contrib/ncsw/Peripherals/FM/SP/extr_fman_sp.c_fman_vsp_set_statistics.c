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
typedef  size_t uint16_t ;
struct fm_pcd_storage_profile_regs {int /*<<< orphan*/  fm_sp_acnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  iowrite32be (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void fman_vsp_set_statistics(struct fm_pcd_storage_profile_regs *regs,
            uint16_t index,	uint32_t value)
{
    struct fm_pcd_storage_profile_regs *sp_regs;
    sp_regs = &regs[index];
    iowrite32be(value, &sp_regs->fm_sp_acnt);
}