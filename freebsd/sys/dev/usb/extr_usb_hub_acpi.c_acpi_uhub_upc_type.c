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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  typelist ;

/* Variables and functions */

__attribute__((used)) static const char *
acpi_uhub_upc_type(uint8_t type)
{
	const char *typelist[] = {"TypeA", "MiniAB", "Express",
				  "USB3-A", "USB3-B", "USB-MicroB",
				  "USB3-MicroAB", "USB3-PowerB",
				  "TypeC-USB2", "TypeC-Switch",
				  "TypeC-nonSwitch"};
	const int last = sizeof(typelist) / sizeof(typelist[0]);

	if (type == 0xff) {
		return "Proprietary";
	}

	return (type < last) ? typelist[type] : "Unknown";
}