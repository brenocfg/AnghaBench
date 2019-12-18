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

/* Variables and functions */
 int /*<<< orphan*/  ACPIIO_ACKSLPSTATE ; 
 int /*<<< orphan*/  EX_IOERR ; 
 int /*<<< orphan*/  acpifd ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void
acpi_sleep_ack(int err_val)
{
	int ret;

	ret = ioctl(acpifd, ACPIIO_ACKSLPSTATE, &err_val);
	if (ret != 0)
		err(EX_IOERR, "ack sleep type failed");
}