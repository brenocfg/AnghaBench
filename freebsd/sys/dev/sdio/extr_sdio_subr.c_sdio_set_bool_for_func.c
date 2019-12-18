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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int SDIO_READ_DIRECT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int SDIO_WRITE_DIRECT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
sdio_set_bool_for_func(device_t dev, uint32_t addr, uint8_t fn, bool enable)
{
	device_t pdev;
	int error;
	uint8_t val;
	bool enabled;

	pdev = device_get_parent(dev);
	error = SDIO_READ_DIRECT(pdev, 0, addr, &val);
	if (error != 0)
		return (error);

	enabled = (val & (1 << fn)) ? true : false;
	if (enabled == enable)
		return (0);

	if (enable)
		val |= (1 << fn);
	else
		val &= ~(1 << fn);
	error = SDIO_WRITE_DIRECT(pdev, 0, addr, val);
	return (error);
}