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
struct TYPE_2__ {scalar_t__ IO_ADDR_W; } ;
struct nand_chip {TYPE_1__ legacy; } ;

/* Variables and functions */
 unsigned int NAND_CLE ; 
 int NAND_CMD_NONE ; 
 int /*<<< orphan*/  writeb (int,scalar_t__) ; 

__attribute__((used)) static void qong_nand_cmd_ctrl(struct nand_chip *nand_chip, int cmd,
			       unsigned int ctrl)
{
	if (cmd == NAND_CMD_NONE)
		return;

	if (ctrl & NAND_CLE)
		writeb(cmd, nand_chip->legacy.IO_ADDR_W + (1 << 24));
	else
		writeb(cmd, nand_chip->legacy.IO_ADDR_W + (1 << 23));
}