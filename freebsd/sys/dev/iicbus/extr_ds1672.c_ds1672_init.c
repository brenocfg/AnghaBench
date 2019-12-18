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
 int /*<<< orphan*/  DS1672_CTRL ; 
 int DS1672_CTRL_EOSC ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int ds1672_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int ds1672_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int
ds1672_init(device_t dev)
{
	uint8_t ctrl;
	int error;

	error = ds1672_read(dev, DS1672_CTRL, &ctrl, 1);
	if (error)
		return (error);

	/*
	 * Check if oscialltor is not runned.
	 */
	if (ctrl & DS1672_CTRL_EOSC) {
		device_printf(dev, "RTC oscillator was stopped. Check system"
		    " time and RTC battery.\n");
		ctrl &= ~DS1672_CTRL_EOSC;	/* Start oscillator. */
		error = ds1672_write(dev, DS1672_CTRL, &ctrl, 1);
	}
	return (error);
}