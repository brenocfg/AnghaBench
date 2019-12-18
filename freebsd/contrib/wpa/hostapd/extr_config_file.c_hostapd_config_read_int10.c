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
 int atoi (char const*) ; 
 char* os_strchr (char const*,char) ; 

__attribute__((used)) static int hostapd_config_read_int10(const char *value)
{
	int i, d;
	char *pos;

	i = atoi(value);
	pos = os_strchr(value, '.');
	d = 0;
	if (pos) {
		pos++;
		if (*pos >= '0' && *pos <= '9')
			d = *pos - '0';
	}

	return i * 10 + d;
}