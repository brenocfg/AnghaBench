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
 int /*<<< orphan*/  DS1672_ADDR ; 
 int /*<<< orphan*/  IIC_M_RD ; 
 int /*<<< orphan*/  IIC_M_WR ; 
 int iicbus_transfer (int /*<<< orphan*/ ,struct iic_msg*,int) ; 

__attribute__((used)) static int
ds1672_read(device_t dev, uint8_t addr, uint8_t *data, uint8_t size)
{
	struct iic_msg msgs[2] = {
	     { DS1672_ADDR, IIC_M_WR, 1, &addr },
	     { DS1672_ADDR, IIC_M_RD, size, data }
	};

	return (iicbus_transfer(dev, msgs, 2));
}