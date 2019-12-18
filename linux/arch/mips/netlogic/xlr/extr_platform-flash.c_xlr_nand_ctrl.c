#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct nand_chip {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  cs; int /*<<< orphan*/  flash_mmio; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLASH_NAND_ALE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FLASH_NAND_CLE (int /*<<< orphan*/ ) ; 
 unsigned int NAND_ALE ; 
 unsigned int NAND_CLE ; 
 TYPE_1__ nand_priv ; 
 int /*<<< orphan*/  nlm_write_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void xlr_nand_ctrl(struct nand_chip *chip, int cmd,
			  unsigned int ctrl)
{
	if (ctrl & NAND_CLE)
		nlm_write_reg(nand_priv.flash_mmio,
			FLASH_NAND_CLE(nand_priv.cs), cmd);
	else if (ctrl & NAND_ALE)
		nlm_write_reg(nand_priv.flash_mmio,
			FLASH_NAND_ALE(nand_priv.cs), cmd);
}