#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  void* u_int32_t ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {void* compatid; void* logicalid; void* serial; void* vendorid; } ;
typedef  TYPE_1__ atkbdc_device_t ;

/* Variables and functions */
 int ENOENT ; 
#define  KBDC_IVAR_COMPATID 131 
#define  KBDC_IVAR_LOGICALID 130 
#define  KBDC_IVAR_SERIAL 129 
#define  KBDC_IVAR_VENDORID 128 
 scalar_t__ device_get_ivars (int /*<<< orphan*/ ) ; 

int
atkbdc_write_ivar(device_t bus, device_t dev, int index, uintptr_t val)
{
	atkbdc_device_t *ivar;

	ivar = (atkbdc_device_t *)device_get_ivars(dev);
	switch (index) {
	case KBDC_IVAR_VENDORID:
		ivar->vendorid = (u_int32_t)val;
		break;
	case KBDC_IVAR_SERIAL:
		ivar->serial = (u_int32_t)val;
		break;
	case KBDC_IVAR_LOGICALID:
		ivar->logicalid = (u_int32_t)val;
		break;
	case KBDC_IVAR_COMPATID:
		ivar->compatid = (u_int32_t)val;
		break;
	default:
		return ENOENT;
	}
	return 0;
}