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
struct atmel_tdes_dev {int /*<<< orphan*/  iclk; int /*<<< orphan*/  hw_version; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  atmel_tdes_get_version (struct atmel_tdes_dev*) ; 
 int /*<<< orphan*/  atmel_tdes_hw_init (struct atmel_tdes_dev*) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void atmel_tdes_hw_version_init(struct atmel_tdes_dev *dd)
{
	atmel_tdes_hw_init(dd);

	dd->hw_version = atmel_tdes_get_version(dd);

	dev_info(dd->dev,
			"version: 0x%x\n", dd->hw_version);

	clk_disable_unprepare(dd->iclk);
}