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
struct TYPE_2__ {int /*<<< orphan*/ * layout; } ;
struct nand_chip {TYPE_1__ ecc; } ;
struct mtd_info {int writesize; struct nand_chip* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  rb1xx_nand_ecclayout ; 

__attribute__((used)) static int rb1xx_nand_fixup(struct mtd_info *mtd)
{
	struct nand_chip *chip = mtd->priv;

	if (mtd->writesize == 512)
		chip->ecc.layout = &rb1xx_nand_ecclayout;

	return 0;
}