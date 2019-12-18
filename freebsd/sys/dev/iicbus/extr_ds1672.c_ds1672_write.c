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
struct iic_msg {int* member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DS1672_ADDR ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IIC_M_WR ; 
 int MAX_IIC_DATA_SIZE ; 
 int iicbus_transfer (int /*<<< orphan*/ ,struct iic_msg*,int) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 

__attribute__((used)) static int
ds1672_write(device_t dev, uint8_t addr, uint8_t *data, uint8_t size)
{
	uint8_t buffer[MAX_IIC_DATA_SIZE + 1];
	struct iic_msg msgs[1] = {
	     { DS1672_ADDR, IIC_M_WR, size + 1, buffer },
	};
	
	if (size > MAX_IIC_DATA_SIZE)
		return (ENOMEM);
	/* NB: register pointer precedes actual data */
	buffer[0] = addr;
	memcpy(buffer + 1, data, size);
	return (iicbus_transfer(dev, msgs, 1));
}