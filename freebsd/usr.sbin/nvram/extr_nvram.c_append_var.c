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
typedef  char const uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char const*,char*,char const*,char const*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static int
append_var(uint8_t *buf, int len, const char *var_name, const char *var_value)
{
	int i, append_len;

	while (len > 0) {
		i = strlen(buf) + 1;
		if (i == 1)
			break;
		len -= i;
		buf += i;
	}
	append_len = strlen(var_name) + strlen(var_value) + 2;
	if (len < append_len)
		return -1;
	sprintf(buf, "%s=%s", var_name, var_value);
	return 0;
}