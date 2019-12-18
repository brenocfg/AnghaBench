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
typedef  int uint64_t ;

/* Variables and functions */
 int ocs_sscanf (char*,char*,scalar_t__*,scalar_t__*,scalar_t__*,scalar_t__*,scalar_t__*,scalar_t__*,scalar_t__*,scalar_t__*) ; 

int
parse_wwn(char *wwn_in, uint64_t *wwn_out)
{
	uint8_t byte0;
	uint8_t byte1;
	uint8_t byte2;
	uint8_t byte3;
	uint8_t byte4;
	uint8_t byte5;
	uint8_t byte6;
	uint8_t byte7;
	int rc;

	rc = ocs_sscanf(wwn_in, "0x%2hhx%2hhx%2hhx%2hhx%2hhx%2hhx%2hhx%2hhx",
				&byte0, &byte1, &byte2, &byte3,
				&byte4, &byte5, &byte6, &byte7);

	if (rc == 8) {
		*wwn_out = ((uint64_t)byte0 << 56) |
				((uint64_t)byte1 << 48) |
				((uint64_t)byte2 << 40) |
				((uint64_t)byte3 << 32) |
				((uint64_t)byte4 << 24) |
				((uint64_t)byte5 << 16) |
				((uint64_t)byte6 <<  8) |
				((uint64_t)byte7);
		return 0;

	} else {
		return 1;
	}
}