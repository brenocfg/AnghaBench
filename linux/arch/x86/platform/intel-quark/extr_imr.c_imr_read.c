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
struct imr_regs {int /*<<< orphan*/  wmask; int /*<<< orphan*/  rmask; int /*<<< orphan*/  addr_hi; int /*<<< orphan*/  addr_lo; } ;
struct imr_device {int reg_base; } ;

/* Variables and functions */
 int IMR_NUM_REGS ; 
 int /*<<< orphan*/  MBI_REG_READ ; 
 int /*<<< orphan*/  QRK_MBI_UNIT_MM ; 
 int iosf_mbi_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int imr_read(struct imr_device *idev, u32 imr_id, struct imr_regs *imr)
{
	u32 reg = imr_id * IMR_NUM_REGS + idev->reg_base;
	int ret;

	ret = iosf_mbi_read(QRK_MBI_UNIT_MM, MBI_REG_READ, reg++, &imr->addr_lo);
	if (ret)
		return ret;

	ret = iosf_mbi_read(QRK_MBI_UNIT_MM, MBI_REG_READ, reg++, &imr->addr_hi);
	if (ret)
		return ret;

	ret = iosf_mbi_read(QRK_MBI_UNIT_MM, MBI_REG_READ, reg++, &imr->rmask);
	if (ret)
		return ret;

	return iosf_mbi_read(QRK_MBI_UNIT_MM, MBI_REG_READ, reg++, &imr->wmask);
}