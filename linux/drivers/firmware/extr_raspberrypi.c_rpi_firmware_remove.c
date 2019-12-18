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
struct rpi_firmware {int /*<<< orphan*/  chan; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mbox_free_channel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_device_unregister (int /*<<< orphan*/ *) ; 
 struct rpi_firmware* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/ * rpi_clk ; 
 int /*<<< orphan*/ * rpi_hwmon ; 

__attribute__((used)) static int rpi_firmware_remove(struct platform_device *pdev)
{
	struct rpi_firmware *fw = platform_get_drvdata(pdev);

	platform_device_unregister(rpi_hwmon);
	rpi_hwmon = NULL;
	platform_device_unregister(rpi_clk);
	rpi_clk = NULL;
	mbox_free_channel(fw->chan);

	return 0;
}