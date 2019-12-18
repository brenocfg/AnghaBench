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
typedef  void* uint8_t ;
typedef  int uint16_t ;
struct iic_msg {int len; void** buf; int /*<<< orphan*/  flags; void* slave; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  IIC_M_RD ; 
 int /*<<< orphan*/  IIC_M_WR ; 
 void* iicbus_get_addr (int /*<<< orphan*/ ) ; 
 int iicbus_transfer_excl (int /*<<< orphan*/ ,struct iic_msg*,int,int) ; 

__attribute__((used)) static int
nxprtc_readfrom(device_t slavedev, uint8_t regaddr, void *buffer,
    uint16_t buflen, int waithow)
{
	struct iic_msg msg;
	int err;
	uint8_t slaveaddr;

	/*
	 * Two transfers back to back with a stop and start between them; first we
	 * write the address-within-device, then we read from the device.  This
	 * is used instead of the standard iicdev_readfrom() because some of the
	 * chips we service don't support i2c repeat-start operations (grrrrr)
	 * so we do two completely separate transfers with a full stop between.
	 */
	slaveaddr = iicbus_get_addr(slavedev);

	msg.slave = slaveaddr;
	msg.flags = IIC_M_WR;
	msg.len   = 1;
	msg.buf   = &regaddr;

	if ((err = iicbus_transfer_excl(slavedev, &msg, 1, waithow)) != 0)
		return (err);

	msg.slave = slaveaddr;
	msg.flags = IIC_M_RD;
	msg.len   = buflen;
	msg.buf   = buffer;

	return (iicbus_transfer_excl(slavedev, &msg, 1, waithow));
}