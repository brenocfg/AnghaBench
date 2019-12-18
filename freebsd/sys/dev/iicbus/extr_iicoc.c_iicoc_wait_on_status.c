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
 int I2C_TIMEOUT ; 
 int /*<<< orphan*/  OC_I2C_STATUS_REG ; 
 int iicoc_dev_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
iicoc_wait_on_status(device_t dev, uint8_t bit)
{
	int tries = I2C_TIMEOUT;
	uint8_t status;

	do {
		status = iicoc_dev_read(dev, OC_I2C_STATUS_REG);
	} while ((status & bit) != 0 && --tries > 0);

	return (tries == 0 ? -1: 0);
}