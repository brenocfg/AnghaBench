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
typedef  uintptr_t u_long ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENOENT ; 
#define  PPBUS_IVAR_MODE 128 
 int /*<<< orphan*/  ppb_get_mode (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ppbus_read_ivar(device_t bus, device_t dev, int index, uintptr_t* val)
{

	switch (index) {
	case PPBUS_IVAR_MODE:
		/* XXX yet device mode = ppbus mode = chipset mode */
		*val = (u_long)ppb_get_mode(bus);
		break;
	default:
		return (ENOENT);
	}

	return (0);
}