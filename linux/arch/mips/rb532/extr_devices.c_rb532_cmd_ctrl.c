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
struct TYPE_2__ {int /*<<< orphan*/  IO_ADDR_W; } ;
struct nand_chip {TYPE_1__ legacy; } ;

/* Variables and functions */
 unsigned int NAND_ALE ; 
 unsigned int NAND_CLE ; 
 int NAND_CMD_NONE ; 
 unsigned int NAND_CTRL_CHANGE ; 
 int /*<<< orphan*/  set_latch_u5 (unsigned char,unsigned char) ; 
 int /*<<< orphan*/  writeb (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rb532_cmd_ctrl(struct nand_chip *chip, int cmd, unsigned int ctrl)
{
	unsigned char orbits, nandbits;

	if (ctrl & NAND_CTRL_CHANGE) {
		orbits = (ctrl & NAND_CLE) << 1;
		orbits |= (ctrl & NAND_ALE) >> 1;

		nandbits = (~ctrl & NAND_CLE) << 1;
		nandbits |= (~ctrl & NAND_ALE) >> 1;

		set_latch_u5(orbits, nandbits);
	}
	if (cmd != NAND_CMD_NONE)
		writeb(cmd, chip->legacy.IO_ADDR_W);
}