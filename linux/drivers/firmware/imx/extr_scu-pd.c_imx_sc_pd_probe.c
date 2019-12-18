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
struct imx_sc_pd_soc {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int imx_scu_get_handle (int /*<<< orphan*/ *) ; 
 int imx_scu_init_pm_domains (int /*<<< orphan*/ *,struct imx_sc_pd_soc const*) ; 
 struct imx_sc_pd_soc* of_device_get_match_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_ipc_handle ; 

__attribute__((used)) static int imx_sc_pd_probe(struct platform_device *pdev)
{
	const struct imx_sc_pd_soc *pd_soc;
	int ret;

	ret = imx_scu_get_handle(&pm_ipc_handle);
	if (ret)
		return ret;

	pd_soc = of_device_get_match_data(&pdev->dev);
	if (!pd_soc)
		return -ENODEV;

	return imx_scu_init_pm_domains(&pdev->dev, pd_soc);
}