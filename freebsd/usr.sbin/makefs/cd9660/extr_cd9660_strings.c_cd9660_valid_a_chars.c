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

/* Variables and functions */
 int /*<<< orphan*/  cd9660_is_a_char (char const) ; 
 scalar_t__ islower (unsigned char) ; 

int
cd9660_valid_a_chars(const char *str)
{
	const char *c = str;
	int upperFound = 0;

	while ((*c) != '\0') {
		if (!(cd9660_is_a_char(*c))) {
			if (islower((unsigned char)*c) )
				upperFound = 1;
			else
				return 0;
		}
		c++;
	}
	return upperFound + 1;
}