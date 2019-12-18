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
typedef  char UINT8 ;

/* Variables and functions */
 scalar_t__ acpi_wmi_hex_to_int (char const*,char*) ; 

__attribute__((used)) static int
acpi_wmi_guid_string_to_guid(const UINT8 *guid_string, UINT8 *guid)
{
	static const int mapping[20] = {3, 2, 1, 0, -1, 5, 4, -1, 7, 6, -1,
	    8, 9, -1, 10, 11, 12, 13, 14, 15};
	int i;

	for (i = 0; i < 20; ++i, ++guid_string) {
		if (mapping[i] >= 0) {
			if (acpi_wmi_hex_to_int(guid_string,
			    &guid[mapping[i]]))
				return (-1);
			++guid_string;
		} else if (*guid_string != '-')
			return (-1);
	}

	return (0);
}