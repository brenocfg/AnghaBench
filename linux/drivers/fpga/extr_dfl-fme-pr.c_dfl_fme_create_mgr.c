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
struct TYPE_2__ {struct TYPE_2__* parent; } ;
struct platform_device {TYPE_1__ dev; int /*<<< orphan*/  id; } ;
struct dfl_fme_mgr_pdata {scalar_t__ ioaddr; } ;
struct dfl_feature_platform_data {struct platform_device* dev; } ;
struct dfl_feature {scalar_t__ ioaddr; } ;
typedef  int /*<<< orphan*/  mgr_pdata ;

/* Variables and functions */
 int /*<<< orphan*/  DFL_FPGA_FME_MGR ; 
 int ENODEV ; 
 int ENOMEM ; 
 struct platform_device* ERR_PTR (int) ; 
 int platform_device_add (struct platform_device*) ; 
 int platform_device_add_data (struct platform_device*,struct dfl_fme_mgr_pdata*,int) ; 
 struct platform_device* platform_device_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_device_put (struct platform_device*) ; 

__attribute__((used)) static struct platform_device *
dfl_fme_create_mgr(struct dfl_feature_platform_data *pdata,
		   struct dfl_feature *feature)
{
	struct platform_device *mgr, *fme = pdata->dev;
	struct dfl_fme_mgr_pdata mgr_pdata;
	int ret = -ENOMEM;

	if (!feature->ioaddr)
		return ERR_PTR(-ENODEV);

	mgr_pdata.ioaddr = feature->ioaddr;

	/*
	 * Each FME has only one fpga-mgr, so allocate platform device using
	 * the same FME platform device id.
	 */
	mgr = platform_device_alloc(DFL_FPGA_FME_MGR, fme->id);
	if (!mgr)
		return ERR_PTR(ret);

	mgr->dev.parent = &fme->dev;

	ret = platform_device_add_data(mgr, &mgr_pdata, sizeof(mgr_pdata));
	if (ret)
		goto create_mgr_err;

	ret = platform_device_add(mgr);
	if (ret)
		goto create_mgr_err;

	return mgr;

create_mgr_err:
	platform_device_put(mgr);
	return ERR_PTR(ret);
}