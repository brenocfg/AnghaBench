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
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ ADB_DEVICE_KEYBOARD ; 
 int ENXIO ; 
 int adb_get_device_handler (int /*<<< orphan*/ ) ; 
 scalar_t__ adb_get_device_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int 
adb_kbd_probe(device_t dev) 
{
	uint8_t type;

	type = adb_get_device_type(dev);

	if (type != ADB_DEVICE_KEYBOARD)
		return (ENXIO);

	switch(adb_get_device_handler(dev)) {
	case 1:
		device_set_desc(dev,"Apple Standard Keyboard");
		break;
	case 2:
		device_set_desc(dev,"Apple Extended Keyboard");
		break;
	case 4:
		device_set_desc(dev,"Apple ISO Keyboard");
		break;
	case 5:
		device_set_desc(dev,"Apple Extended ISO Keyboard");
		break;
	case 8:
		device_set_desc(dev,"Apple Keyboard II");
		break;
	case 9:
		device_set_desc(dev,"Apple ISO Keyboard II");
		break;
	case 12:
		device_set_desc(dev,"PowerBook Keyboard");
		break;
	case 13:
		device_set_desc(dev,"PowerBook ISO Keyboard");
		break;
	case 24:
		device_set_desc(dev,"PowerBook Extended Keyboard");
		break;
	case 27:
		device_set_desc(dev,"Apple Design Keyboard");
		break;
	case 195:
		device_set_desc(dev,"PowerBook G3 Keyboard");
		break;
	case 196:
		device_set_desc(dev,"iBook Keyboard");
		break;
	default:
		device_set_desc(dev,"ADB Keyboard");
		break;
	}

	return (0);
}