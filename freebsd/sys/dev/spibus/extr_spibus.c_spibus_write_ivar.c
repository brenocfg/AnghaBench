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
typedef  void* uint32_t ;
struct spibus_ivar {void* mode; void* clock; } ;
typedef  scalar_t__ device_t ;

/* Variables and functions */
 int EDOOFUS ; 
 int EINVAL ; 
 struct spibus_ivar* SPIBUS_IVAR (scalar_t__) ; 
#define  SPIBUS_IVAR_CLOCK 130 
#define  SPIBUS_IVAR_CS 129 
#define  SPIBUS_IVAR_MODE 128 
 scalar_t__ device_get_parent (scalar_t__) ; 

__attribute__((used)) static int
spibus_write_ivar(device_t bus, device_t child, int which, uintptr_t value)
{
	struct spibus_ivar *devi = SPIBUS_IVAR(child);

	if (devi == NULL || device_get_parent(child) != bus)
		return (EDOOFUS);

	switch (which) {
	case SPIBUS_IVAR_CLOCK:
		/* Any non-zero value is allowed for max clock frequency. */
		if (value == 0)
			return (EINVAL);
		devi->clock = (uint32_t)value;
		break;
	case SPIBUS_IVAR_CS:
		 /* Chip select cannot be changed. */
		return (EINVAL);
	case SPIBUS_IVAR_MODE:
		/* Valid SPI modes are 0-3. */
		if (value > 3)
			return (EINVAL);
		devi->mode = (uint32_t)value;
		break;
	default:
		return (EINVAL);
	}

	return (0);
}