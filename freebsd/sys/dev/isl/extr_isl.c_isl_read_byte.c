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
typedef  int /*<<< orphan*/  uint16_t ;
struct iic_msg {int member_1; int member_2; int /*<<< orphan*/ * member_3; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int IIC_M_NOSTOP ; 
 int IIC_M_RD ; 
 int IIC_M_WR ; 
 int /*<<< orphan*/  iicbus_get_addr (int /*<<< orphan*/ ) ; 
 int iicbus_transfer (int /*<<< orphan*/ ,struct iic_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nitems (struct iic_msg*) ; 

__attribute__((used)) static int
isl_read_byte(device_t dev, uint8_t reg, uint8_t *val)
{
	uint16_t addr = iicbus_get_addr(dev);
	struct iic_msg msgs[] = {
	     { addr, IIC_M_WR | IIC_M_NOSTOP, 1, &reg },
	     { addr, IIC_M_RD, 1, val },
	};

	return (iicbus_transfer(dev, msgs, nitems(msgs)));
}