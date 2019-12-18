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
 int /*<<< orphan*/  NAND_REG_DATA ; 
 int /*<<< orphan*/  NAND_WRITE_REG (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  adm5120_nand_set_ale (unsigned int) ; 
 int /*<<< orphan*/  adm5120_nand_set_cen (unsigned int) ; 
 int /*<<< orphan*/  adm5120_nand_set_cle (unsigned int) ; 

__attribute__((used)) static void adm5120_nand_cmd_ctrl(struct mtd_info *mtd, int cmd,
					unsigned int ctrl)
{
	if (ctrl & NAND_CTRL_CHANGE) {
		adm5120_nand_set_cle(ctrl & NAND_CLE);
		adm5120_nand_set_ale(ctrl & NAND_ALE);
		adm5120_nand_set_cen(ctrl & NAND_NCE);
	}

	if (cmd != NAND_CMD_NONE)
		NAND_WRITE_REG(NAND_REG_DATA, cmd);
}