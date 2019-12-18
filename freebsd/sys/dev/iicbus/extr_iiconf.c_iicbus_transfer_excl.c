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
typedef  int /*<<< orphan*/  uint32_t ;
struct iic_msg {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int IICBUS_TRANSFER (int /*<<< orphan*/ ,struct iic_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iicbus_release_bus (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int iicbus_request_bus (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int
iicbus_transfer_excl(device_t dev, struct iic_msg *msgs, uint32_t nmsgs,
    int how)
{
	device_t bus;
	int error;

	bus = device_get_parent(dev);
	error = iicbus_request_bus(bus, dev, how);
	if (error == 0)
		error = IICBUS_TRANSFER(bus, msgs, nmsgs);
	iicbus_release_bus(bus, dev);
	return (error);
}