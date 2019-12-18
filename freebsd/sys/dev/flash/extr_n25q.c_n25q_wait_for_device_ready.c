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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_READ_STATUS ; 
 int QSPI_READ_REG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int STATUS_WIP ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
n25q_wait_for_device_ready(device_t dev)
{
	device_t pdev;
	uint8_t status;
	int err;

	pdev = device_get_parent(dev);

	do {
		err = QSPI_READ_REG(pdev, dev, CMD_READ_STATUS, &status, 1);
	} while (err == 0 && (status & STATUS_WIP));

	return (err);
}