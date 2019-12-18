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
struct iic_msg {int flags; int len; void** buf; void* slave; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int IIC_M_NOSTOP ; 
 int IIC_M_RD ; 
 int IIC_M_WR ; 
 void* iicbus_get_addr (int /*<<< orphan*/ ) ; 
 int iicbus_transfer_excl (int /*<<< orphan*/ ,struct iic_msg*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nitems (struct iic_msg*) ; 

int
iicdev_readfrom(device_t slavedev, uint8_t regaddr, void *buffer,
    uint16_t buflen, int waithow)
{
	struct iic_msg msgs[2];
	uint8_t slaveaddr;

	/*
	 * Two transfers back to back with a repeat-start between them; first we
	 * write the address-within-device, then we read from the device.
	 */
	slaveaddr = iicbus_get_addr(slavedev);

	msgs[0].slave = slaveaddr;
	msgs[0].flags = IIC_M_WR | IIC_M_NOSTOP;
	msgs[0].len   = 1;
	msgs[0].buf   = &regaddr;

	msgs[1].slave = slaveaddr;
	msgs[1].flags = IIC_M_RD;
	msgs[1].len   = buflen;
	msgs[1].buf   = buffer;

	return (iicbus_transfer_excl(slavedev, msgs, nitems(msgs), waithow));
}