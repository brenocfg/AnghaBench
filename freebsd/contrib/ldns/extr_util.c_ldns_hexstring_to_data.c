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

/* Variables and functions */
 scalar_t__ ldns_hexdigit_to_int (char const) ; 
 int strlen (char const*) ; 

int
ldns_hexstring_to_data(uint8_t *data, const char *str)
{
	size_t i;

	if (!str || !data) {
		return -1;
	}

	if (strlen(str) % 2 != 0) {
		return -2;
	}

	for (i = 0; i < strlen(str) / 2; i++) {
		data[i] =
			16 * (uint8_t) ldns_hexdigit_to_int(str[i*2]) +
			(uint8_t) ldns_hexdigit_to_int(str[i*2 + 1]);
	}

	return (int) i;
}