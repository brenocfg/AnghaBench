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
struct iic_msg {int member_2; int* member_3; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AD7418_ADDR ; 
 int /*<<< orphan*/  IIC_M_WR ; 
 int iicbus_transfer (int /*<<< orphan*/ ,struct iic_msg*,int) ; 

__attribute__((used)) static int
ad7418_write_1(device_t dev, int reg, int v) 
{
	/* NB: register pointer precedes actual data */
	uint8_t data[2];
	struct iic_msg msgs[1] = {
	     { AD7418_ADDR, IIC_M_WR, 2, data },
	};
	data[0] = reg;
	data[1] = v & 0xff;
	return iicbus_transfer(dev, msgs, 1);
}