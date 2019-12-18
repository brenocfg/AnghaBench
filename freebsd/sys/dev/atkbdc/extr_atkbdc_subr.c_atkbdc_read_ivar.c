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
typedef  uintptr_t u_long ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int /*<<< orphan*/  compatid; int /*<<< orphan*/  logicalid; int /*<<< orphan*/  serial; int /*<<< orphan*/  vendorid; } ;
typedef  TYPE_1__ atkbdc_device_t ;

/* Variables and functions */
 int ENOENT ; 
#define  KBDC_IVAR_COMPATID 131 
#define  KBDC_IVAR_LOGICALID 130 
#define  KBDC_IVAR_SERIAL 129 
#define  KBDC_IVAR_VENDORID 128 
 scalar_t__ device_get_ivars (int /*<<< orphan*/ ) ; 

int
atkbdc_read_ivar(device_t bus, device_t dev, int index, uintptr_t *val)
{
	atkbdc_device_t *ivar;

	ivar = (atkbdc_device_t *)device_get_ivars(dev);
	switch (index) {
	case KBDC_IVAR_VENDORID:
		*val = (u_long)ivar->vendorid;
		break;
	case KBDC_IVAR_SERIAL:
		*val = (u_long)ivar->serial;
		break;
	case KBDC_IVAR_LOGICALID:
		*val = (u_long)ivar->logicalid;
		break;
	case KBDC_IVAR_COMPATID:
		*val = (u_long)ivar->compatid;
		break;
	default:
		return ENOENT;
	}
	return 0;
}