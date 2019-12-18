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
struct rpi_firmware {int dummy; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RPI_FIRMWARE_NOTIFY_REBOOT ; 
 struct rpi_firmware* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  rpi_firmware_property (struct rpi_firmware*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rpi_firmware_shutdown(struct platform_device *pdev)
{
	struct rpi_firmware *fw = platform_get_drvdata(pdev);

	if (!fw)
		return;

	rpi_firmware_property(fw, RPI_FIRMWARE_NOTIFY_REBOOT, NULL, 0);
}