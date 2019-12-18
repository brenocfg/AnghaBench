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
struct dfl_fpga_port_ops {int (* get_id ) (struct platform_device*) ;} ;
struct dfl_feature_platform_data {int id; } ;

/* Variables and functions */
 int FEATURE_DEV_ID_UNUSED ; 
 struct dfl_feature_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 struct dfl_fpga_port_ops* dfl_fpga_port_ops_get (struct platform_device*) ; 
 int /*<<< orphan*/  dfl_fpga_port_ops_put (struct dfl_fpga_port_ops*) ; 
 int stub1 (struct platform_device*) ; 

int dfl_fpga_check_port_id(struct platform_device *pdev, void *pport_id)
{
	struct dfl_feature_platform_data *pdata = dev_get_platdata(&pdev->dev);
	struct dfl_fpga_port_ops *port_ops;

	if (pdata->id != FEATURE_DEV_ID_UNUSED)
		return pdata->id == *(int *)pport_id;

	port_ops = dfl_fpga_port_ops_get(pdev);
	if (!port_ops || !port_ops->get_id)
		return 0;

	pdata->id = port_ops->get_id(pdev);
	dfl_fpga_port_ops_put(port_ops);

	return pdata->id == *(int *)pport_id;
}