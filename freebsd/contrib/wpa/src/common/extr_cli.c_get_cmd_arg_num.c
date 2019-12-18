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

int get_cmd_arg_num(const char *str, int pos)
{
	int arg = 0, i;

	for (i = 0; i <= pos; i++) {
		if (str[i] != ' ') {
			arg++;
			while (i <= pos && str[i] != ' ')
				i++;
		}
	}

	if (arg > 0)
		arg--;
	return arg;
}