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
 int /*<<< orphan*/  Error (char*,char*) ; 

int ParseHex (char *hex)
{
	char    *str;
	int    num;

	num = 0;
	str = hex;

	while (*str)
	{
		num <<= 4;
		if (*str >= '0' && *str <= '9')
			num += *str-'0';
		else if (*str >= 'a' && *str <= 'f')
			num += 10 + *str-'a';
		else if (*str >= 'A' && *str <= 'F')
			num += 10 + *str-'A';
		else
			Error ("Bad hex number: %s",hex);
		str++;
	}

	return num;
}