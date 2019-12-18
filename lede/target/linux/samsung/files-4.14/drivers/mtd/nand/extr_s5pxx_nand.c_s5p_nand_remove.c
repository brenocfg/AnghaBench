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
struct s5p_nand_host {int /*<<< orphan*/ * clk; int /*<<< orphan*/  nand_chip; } ;
struct platform_device {int dummy; } ;
struct mtd_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nand_release (struct mtd_info*) ; 
 struct mtd_info* nand_to_mtd (int /*<<< orphan*/ *) ; 
 struct s5p_nand_host* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int s5p_nand_remove(struct platform_device *pdev)
{
	struct s5p_nand_host *host = platform_get_drvdata(pdev);
	struct mtd_info *mtd = nand_to_mtd(&host->nand_chip);

	nand_release(mtd);
	clk_disable_unprepare(host->clk[0]);	/* nandxl */
	clk_disable_unprepare(host->clk[1]);	/* nand */

	return 0;
}