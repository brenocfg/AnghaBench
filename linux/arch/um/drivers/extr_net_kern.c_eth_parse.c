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
 int EINVAL ; 
 scalar_t__ find_device (int) ; 
 int simple_strtoul (char*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int eth_parse(char *str, int *index_out, char **str_out,
		     char **error_out)
{
	char *end;
	int n, err = -EINVAL;

	n = simple_strtoul(str, &end, 0);
	if (end == str) {
		*error_out = "Bad device number";
		return err;
	}

	str = end;
	if (*str != '=') {
		*error_out = "Expected '=' after device number";
		return err;
	}

	str++;
	if (find_device(n)) {
		*error_out = "Device already configured";
		return err;
	}

	*index_out = n;
	*str_out = str;
	return 0;
}