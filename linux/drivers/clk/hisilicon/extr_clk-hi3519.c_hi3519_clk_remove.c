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
struct platform_device {int dummy; } ;
struct hi3519_crg_data {int /*<<< orphan*/  rstc; } ;

/* Variables and functions */
 int /*<<< orphan*/  hi3519_clk_unregister (struct platform_device*) ; 
 int /*<<< orphan*/  hisi_reset_exit (int /*<<< orphan*/ ) ; 
 struct hi3519_crg_data* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int hi3519_clk_remove(struct platform_device *pdev)
{
	struct hi3519_crg_data *crg = platform_get_drvdata(pdev);

	hisi_reset_exit(crg->rstc);
	hi3519_clk_unregister(pdev);
	return 0;
}