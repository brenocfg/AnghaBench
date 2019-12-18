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
typedef  char uint8_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int IIC_EBUSERR ; 
 int IIC_NOERR ; 
 char OC_COMMAND_RDNACK ; 
 char OC_COMMAND_READ ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int iicoc_rd_cmd (int /*<<< orphan*/ ,char) ; 

__attribute__((used)) static int 
iicoc_read(device_t dev, char *buf, int len, int *read, int last,
    int delay)
{
	int data, i;
	uint8_t cmd;

	for (i = 0; i < len; i++) {
		/* Read data byte */
		cmd = (i == len - 1) ? OC_COMMAND_RDNACK : OC_COMMAND_READ;
		data = iicoc_rd_cmd(dev, cmd);
		if (data < 0) {
			device_printf(dev, 
			    "I2C read data byte %d failed.\n", i);
			goto i2c_rx_error;
		}
		buf[i] = (uint8_t)data;
	}
	
	*read = len;
	return (IIC_NOERR);

i2c_rx_error:	
	return (IIC_EBUSERR);
}