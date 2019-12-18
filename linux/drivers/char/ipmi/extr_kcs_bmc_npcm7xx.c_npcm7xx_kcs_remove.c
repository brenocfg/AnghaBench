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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct kcs_bmc {int /*<<< orphan*/  miscdev; } ;

/* Variables and functions */
 struct kcs_bmc* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  misc_deregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int npcm7xx_kcs_remove(struct platform_device *pdev)
{
	struct kcs_bmc *kcs_bmc = dev_get_drvdata(&pdev->dev);

	misc_deregister(&kcs_bmc->miscdev);

	return 0;
}