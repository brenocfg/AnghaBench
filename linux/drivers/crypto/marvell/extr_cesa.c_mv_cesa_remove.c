#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int dummy; } ;
struct mv_cesa_dev {TYPE_2__* engines; TYPE_1__* caps; } ;
struct TYPE_4__ {int /*<<< orphan*/  clk; int /*<<< orphan*/  zclk; } ;
struct TYPE_3__ {int nengines; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mv_cesa_put_sram (struct platform_device*,int) ; 
 int /*<<< orphan*/  mv_cesa_remove_algs (struct mv_cesa_dev*) ; 
 struct mv_cesa_dev* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int mv_cesa_remove(struct platform_device *pdev)
{
	struct mv_cesa_dev *cesa = platform_get_drvdata(pdev);
	int i;

	mv_cesa_remove_algs(cesa);

	for (i = 0; i < cesa->caps->nengines; i++) {
		clk_disable_unprepare(cesa->engines[i].zclk);
		clk_disable_unprepare(cesa->engines[i].clk);
		mv_cesa_put_sram(pdev, i);
	}

	return 0;
}