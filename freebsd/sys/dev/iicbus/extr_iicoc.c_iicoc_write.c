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
 int /*<<< orphan*/  OC_COMMAND_WRITE ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ iicoc_wr_ack_cmd (int /*<<< orphan*/ ,char,int /*<<< orphan*/ ) ; 
 scalar_t__ iicoc_wr_cmd (int /*<<< orphan*/ ,char,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int 
iicoc_write(device_t dev, const char *buf, int len,
    int *sent, int timeout /* us */ )
{
	uint8_t value;
	int i;

	value = buf[0];
	/* Write Slave Offset */
	if (iicoc_wr_ack_cmd(dev, value, OC_COMMAND_WRITE)) {
		device_printf(dev, "I2C write slave offset failed.\n");
		goto i2c_tx_error;	
	}

	for (i = 1; i < len; i++) {
		/* Write data byte */
		value = buf[i];
		if (iicoc_wr_cmd(dev, value, OC_COMMAND_WRITE)) {
			device_printf(dev, "I2C write data byte %d failed.\n",
			    i);
			goto i2c_tx_error;	
		}
	}
	*sent = len;
	return (IIC_NOERR);

i2c_tx_error:
	return (IIC_EBUSERR);
}