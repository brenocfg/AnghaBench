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
struct switch_dev {int dummy; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  MV_GLOBAL2REG (int /*<<< orphan*/ ) ; 
 int MV_INDIRECT_ADDR_S ; 
 int /*<<< orphan*/  MV_INDIRECT_INPROGRESS ; 
 int MV_INDIRECT_READ ; 
 int /*<<< orphan*/  SMI_DATA ; 
 int /*<<< orphan*/  SMI_OP ; 
 scalar_t__ mvsw61xx_wait_mask_s (struct switch_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sr16 (struct switch_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sw16 (struct switch_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
mvsw61xx_mdio_read(struct switch_dev *dev, int addr, int reg)
{
	sw16(dev, MV_GLOBAL2REG(SMI_OP),
	     MV_INDIRECT_READ | (addr << MV_INDIRECT_ADDR_S) | reg);

	if (mvsw61xx_wait_mask_s(dev,  MV_GLOBAL2REG(SMI_OP),
				 MV_INDIRECT_INPROGRESS, 0) < 0)
		return -ETIMEDOUT;

	return sr16(dev, MV_GLOBAL2REG(SMI_DATA));
}