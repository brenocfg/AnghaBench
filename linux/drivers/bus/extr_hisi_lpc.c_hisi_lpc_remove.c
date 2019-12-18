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
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct logic_pio_hwaddr {int dummy; } ;
struct hisi_lpc_dev {struct logic_pio_hwaddr* io_host; } ;
struct acpi_device {int dummy; } ;

/* Variables and functions */
 struct acpi_device* ACPI_COMPANION (struct device*) ; 
 struct hisi_lpc_dev* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  hisi_lpc_acpi_remove (struct device*) ; 
 int /*<<< orphan*/  logic_pio_unregister_range (struct logic_pio_hwaddr*) ; 
 int /*<<< orphan*/  of_platform_depopulate (struct device*) ; 

__attribute__((used)) static int hisi_lpc_remove(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct acpi_device *acpi_device = ACPI_COMPANION(dev);
	struct hisi_lpc_dev *lpcdev = dev_get_drvdata(dev);
	struct logic_pio_hwaddr *range = lpcdev->io_host;

	if (acpi_device)
		hisi_lpc_acpi_remove(dev);
	else
		of_platform_depopulate(dev);

	logic_pio_unregister_range(range);

	return 0;
}