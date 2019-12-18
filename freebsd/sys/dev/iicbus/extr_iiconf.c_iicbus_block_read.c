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
typedef  int u_char ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  IIC_LAST_READ ; 
 int LSB ; 
 int iicbus_read (int /*<<< orphan*/ ,char*,int,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int iicbus_start (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iicbus_stop (int /*<<< orphan*/ ) ; 

int
iicbus_block_read(device_t bus, u_char slave, char *buf, int len, int *read)
{
	u_char addr = slave | LSB;
	int error;

	if ((error = iicbus_start(bus, addr, 0)))
		return (error);

	error = iicbus_read(bus, buf, len, read, IIC_LAST_READ, 0);

	iicbus_stop(bus);

	return (error);
}