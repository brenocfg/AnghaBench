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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct iic_msg {int member_1; int member_2; int /*<<< orphan*/ * member_3; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int IIC_M_NOSTOP ; 
 int IIC_M_RD ; 
 int IIC_M_WR ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hz ; 
 int iicbus_transfer (int /*<<< orphan*/ ,struct iic_msg*,int) ; 
 int /*<<< orphan*/  pause (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ds1775_read_2(device_t dev, uint32_t addr, uint8_t reg, uint16_t *data)
{
	uint8_t buf[4];
	int err, try = 0;

	struct iic_msg msg[2] = {
	    { addr, IIC_M_WR | IIC_M_NOSTOP, 1, &reg },
	    { addr, IIC_M_RD, 2, buf },
	};

	for (;;)
	{
		err = iicbus_transfer(dev, msg, 2);
		if (err != 0)
			goto retry;

		*data = *((uint16_t*)buf);
		return (0);
	retry:
		if (++try > 5) {
			device_printf(dev, "iicbus read failed\n");
			return (-1);
		}
		pause("ds1775_read_2", hz);
	}
}