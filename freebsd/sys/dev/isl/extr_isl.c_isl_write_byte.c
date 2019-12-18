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
struct iic_msg {struct iic_msg* member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  struct iic_msg uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  IIC_M_WR ; 
 int /*<<< orphan*/  iicbus_get_addr (int /*<<< orphan*/ ) ; 
 int iicbus_transfer (int /*<<< orphan*/ ,struct iic_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nitems (struct iic_msg*) ; 

__attribute__((used)) static int
isl_write_byte(device_t dev, uint8_t reg, uint8_t val)
{
	uint16_t addr = iicbus_get_addr(dev);
	uint8_t bytes[] = { reg, val };
	struct iic_msg msgs[] = {
	     { addr, IIC_M_WR, nitems(bytes), bytes },
	};

	return (iicbus_transfer(dev, msgs, nitems(msgs)));
}