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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  REG_CMD1 ; 
 int /*<<< orphan*/  REG_TEST ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int hz ; 
 int isl_write_byte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pause (char*,int) ; 

__attribute__((used)) static int
init_device(device_t dev, int probe)
{
	int error;

	/*
	 * init procedure: send 0x00 to test ref and cmd reg 1
	 */
	error = isl_write_byte(dev, REG_TEST, 0);
	if (error)
		goto done;
	error = isl_write_byte(dev, REG_CMD1, 0);
	if (error)
		goto done;

	pause("islinit", hz/100);

done:
	if (error && !probe)
		device_printf(dev, "Unable to initialize\n");
	return (error);
}