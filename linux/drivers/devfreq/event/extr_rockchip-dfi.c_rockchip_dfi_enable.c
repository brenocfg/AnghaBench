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
struct rockchip_dfi {int /*<<< orphan*/  clk; } ;
struct devfreq_event_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct rockchip_dfi* devfreq_event_get_drvdata (struct devfreq_event_dev*) ; 
 int /*<<< orphan*/  rockchip_dfi_start_hardware_counter (struct devfreq_event_dev*) ; 

__attribute__((used)) static int rockchip_dfi_enable(struct devfreq_event_dev *edev)
{
	struct rockchip_dfi *info = devfreq_event_get_drvdata(edev);
	int ret;

	ret = clk_prepare_enable(info->clk);
	if (ret) {
		dev_err(&edev->dev, "failed to enable dfi clk: %d\n", ret);
		return ret;
	}

	rockchip_dfi_start_hardware_counter(edev);
	return 0;
}