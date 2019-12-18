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
struct smbus_ivar {scalar_t__ addr; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct smbus_ivar* device_get_ivars (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,scalar_t__) ; 

__attribute__((used)) static void
smbus_probe_nomatch(device_t bus, device_t child)
{
	struct smbus_ivar *devi = device_get_ivars(child);

	/*
	 * Ignore (self-identified) devices without a slave address set.
	 * For example, smb(4).
	 */
	if (devi->addr != 0)
		device_printf(bus, "<unknown device> at addr %#x\n",
		    devi->addr);
}