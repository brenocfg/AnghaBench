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
struct sifive_edac_priv {int /*<<< orphan*/  dci; int /*<<< orphan*/  notifier; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  edac_device_del_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  edac_device_free_ctl_info (int /*<<< orphan*/ ) ; 
 struct sifive_edac_priv* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  unregister_sifive_l2_error_notifier (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ecc_unregister(struct platform_device *pdev)
{
	struct sifive_edac_priv *p = platform_get_drvdata(pdev);

	unregister_sifive_l2_error_notifier(&p->notifier);
	edac_device_del_device(&pdev->dev);
	edac_device_free_ctl_info(p->dci);

	return 0;
}