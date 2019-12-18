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
 int IICBB_RESET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 
 int IIC_ENOADDR ; 
 int /*<<< orphan*/  IIC_FASTEST ; 
 scalar_t__ bus_print_child_header (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* device_get_nameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 scalar_t__ printf (char*,char*,...) ; 

__attribute__((used)) static int
iicbb_print_child(device_t bus, device_t dev)
{
	int error;
	int retval = 0;
	u_char oldaddr;

	retval += bus_print_child_header(bus, dev);
	/* retrieve the interface I2C address */
	error = IICBB_RESET(device_get_parent(bus), IIC_FASTEST, 0, &oldaddr);
	if (error == IIC_ENOADDR) {
		retval += printf(" on %s master-only\n",
				 device_get_nameunit(bus));
	} else {
		/* restore the address */
		IICBB_RESET(device_get_parent(bus), IIC_FASTEST, oldaddr, NULL);

		retval += printf(" on %s addr 0x%x\n",
				 device_get_nameunit(bus), oldaddr & 0xff);
	}

	return (retval);
}