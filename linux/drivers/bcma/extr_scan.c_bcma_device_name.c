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
struct bcma_device_id_name {scalar_t__ id; char const* name; } ;
struct bcma_device_id {int manuf; scalar_t__ id; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct bcma_device_id_name*) ; 
#define  BCMA_MANUF_ARM 130 
#define  BCMA_MANUF_BCM 129 
#define  BCMA_MANUF_MIPS 128 
 struct bcma_device_id_name* bcma_arm_device_names ; 
 struct bcma_device_id_name* bcma_bcm_device_names ; 
 struct bcma_device_id_name* bcma_mips_device_names ; 

__attribute__((used)) static const char *bcma_device_name(const struct bcma_device_id *id)
{
	const struct bcma_device_id_name *names;
	int size, i;

	/* search manufacturer specific names */
	switch (id->manuf) {
	case BCMA_MANUF_ARM:
		names = bcma_arm_device_names;
		size = ARRAY_SIZE(bcma_arm_device_names);
		break;
	case BCMA_MANUF_BCM:
		names = bcma_bcm_device_names;
		size = ARRAY_SIZE(bcma_bcm_device_names);
		break;
	case BCMA_MANUF_MIPS:
		names = bcma_mips_device_names;
		size = ARRAY_SIZE(bcma_mips_device_names);
		break;
	default:
		return "UNKNOWN";
	}

	for (i = 0; i < size; i++) {
		if (names[i].id == id->id)
			return names[i].name;
	}

	return "UNKNOWN";
}