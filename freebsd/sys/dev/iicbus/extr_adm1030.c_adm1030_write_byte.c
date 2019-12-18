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
typedef  unsigned char uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct iic_msg {unsigned char* member_3; int len; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  IIC_M_WR ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hz ; 
 scalar_t__ iicbus_transfer (int /*<<< orphan*/ ,struct iic_msg*,int) ; 
 int /*<<< orphan*/  pause (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
adm1030_write_byte(device_t dev, uint32_t addr, uint8_t reg, uint8_t byte)
{
	unsigned char	buf[4];
	int try = 0;

	struct iic_msg	msg[] = {
		{addr, IIC_M_WR, 0, buf}
	};

	msg[0].len = 2;
	buf[0] = reg;
	buf[1] = byte;

	for (;;)
	{
		if (iicbus_transfer(dev, msg, 1) == 0)
			return (0);

		if (++try > 5) {
			device_printf(dev, "iicbus write failed\n");
			return (-1);
		}
		pause("adm1030_write_byte", hz);
	}
}