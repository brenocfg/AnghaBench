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

__attribute__((used)) static void
cuse_str_filter(char *ptr)
{
	int c;

	while (((c = *ptr) != 0)) {

		if ((c >= 'a') && (c <= 'z')) {
			ptr++;
			continue;
		}
		if ((c >= 'A') && (c <= 'Z')) {
			ptr++;
			continue;
		}
		if ((c >= '0') && (c <= '9')) {
			ptr++;
			continue;
		}
		if ((c == '.') || (c == '_') || (c == '/')) {
			ptr++;
			continue;
		}
		*ptr = '_';

		ptr++;
	}
}