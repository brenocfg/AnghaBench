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
struct st_ahci_drv_data {int /*<<< orphan*/ * pwr_rst; int /*<<< orphan*/ * sw_rst; int /*<<< orphan*/ * pwr; } ;
struct device {int dummy; } ;
struct ahci_host_priv {struct st_ahci_drv_data* plat_data; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 void* devm_reset_control_get (struct device*,char*) ; 
 int st_ahci_deassert_resets (struct ahci_host_priv*,struct device*) ; 

__attribute__((used)) static int st_ahci_probe_resets(struct ahci_host_priv *hpriv,
				struct device *dev)
{
	struct st_ahci_drv_data *drv_data = hpriv->plat_data;

	drv_data->pwr = devm_reset_control_get(dev, "pwr-dwn");
	if (IS_ERR(drv_data->pwr)) {
		dev_info(dev, "power reset control not defined\n");
		drv_data->pwr = NULL;
	}

	drv_data->sw_rst = devm_reset_control_get(dev, "sw-rst");
	if (IS_ERR(drv_data->sw_rst)) {
		dev_info(dev, "soft reset control not defined\n");
		drv_data->sw_rst = NULL;
	}

	drv_data->pwr_rst = devm_reset_control_get(dev, "pwr-rst");
	if (IS_ERR(drv_data->pwr_rst)) {
		dev_dbg(dev, "power soft reset control not defined\n");
		drv_data->pwr_rst = NULL;
	}

	return st_ahci_deassert_resets(hpriv, dev);
}