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

/* Variables and functions */
 int ENOENT ; 
#define  PPBUS_IVAR_MODE 128 
 int /*<<< orphan*/  ppb_set_mode (int /*<<< orphan*/ ,uintptr_t) ; 

__attribute__((used)) static int
ppbus_write_ivar(device_t bus, device_t dev, int index, uintptr_t val)
{

	switch (index) {
	case PPBUS_IVAR_MODE:
		/* XXX yet device mode = ppbus mode = chipset mode */
		ppb_set_mode(bus, val);
		break;
	default:
		return (ENOENT);
  	}

	return (0);
}