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
struct mtd_info {int dummy; } ;

/* Variables and functions */
 unsigned int NAND_ALE ; 
 unsigned int NAND_CLE ; 
 int NAND_CMD_NONE ; 
 unsigned int NAND_CTRL_CHANGE ; 
 unsigned int NAND_NCE ; 
 int /*<<< orphan*/  RB150_GPIO_NAND_ALE ; 
 int /*<<< orphan*/  RB150_GPIO_NAND_CLE ; 
 int /*<<< orphan*/  RB150_GPIO_NAND_NCE ; 
 int /*<<< orphan*/  RB150_NAND_DELAY ; 
 int /*<<< orphan*/  RB150_NAND_WRITE (int) ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rb150_nand_cmd_ctrl(struct mtd_info *mtd, int cmd,
		unsigned int ctrl)
{
	if (ctrl & NAND_CTRL_CHANGE) {
		gpio_set_value(RB150_GPIO_NAND_CLE, (ctrl & NAND_CLE) ? 1 : 0);
		gpio_set_value(RB150_GPIO_NAND_ALE, (ctrl & NAND_ALE) ? 1 : 0);
		gpio_set_value(RB150_GPIO_NAND_NCE, (ctrl & NAND_NCE) ? 0 : 1);
	}

	udelay(RB150_NAND_DELAY);

	if (cmd != NAND_CMD_NONE)
		RB150_NAND_WRITE(cmd);
}