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
struct platform_device {int dummy; } ;
struct hisi_crg_dev {TYPE_1__* funcs; int /*<<< orphan*/  rstc; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* unregister_clks ) (struct platform_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  hisi_reset_exit (int /*<<< orphan*/ ) ; 
 struct hisi_crg_dev* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  stub1 (struct platform_device*) ; 

__attribute__((used)) static int hi3798cv200_crg_remove(struct platform_device *pdev)
{
	struct hisi_crg_dev *crg = platform_get_drvdata(pdev);

	hisi_reset_exit(crg->rstc);
	crg->funcs->unregister_clks(pdev);
	return 0;
}