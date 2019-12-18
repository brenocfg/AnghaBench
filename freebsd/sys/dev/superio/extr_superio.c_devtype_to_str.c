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
typedef  int superio_dev_type_t ;

/* Variables and functions */
#define  SUPERIO_DEV_GPIO 132 
#define  SUPERIO_DEV_HWM 131 
#define  SUPERIO_DEV_MAX 130 
#define  SUPERIO_DEV_NONE 129 
#define  SUPERIO_DEV_WDT 128 

__attribute__((used)) static const char *
devtype_to_str(superio_dev_type_t type)
{
	switch (type) {
	case SUPERIO_DEV_NONE:
		return ("none");
	case SUPERIO_DEV_HWM:
		return ("HWM");
	case SUPERIO_DEV_WDT:
		return ("WDT");
	case SUPERIO_DEV_GPIO:
		return ("GPIO");
	case SUPERIO_DEV_MAX:
		return ("invalid");
	}
	return ("invalid");
}