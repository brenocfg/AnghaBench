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
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int EINVAL ; 
#define  IIC_RELEASE_BUS 129 
#define  IIC_REQUEST_BUS 128 

__attribute__((used)) static int
opal_i2c_callback(device_t dev, int index, caddr_t data)
{
	int error = 0;

	switch (index) {
	case IIC_REQUEST_BUS:
		break;

	case IIC_RELEASE_BUS:
		break;

	default:
		error = EINVAL;
	}

	return (error);
}