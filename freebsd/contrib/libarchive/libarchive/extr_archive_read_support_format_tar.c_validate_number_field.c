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

__attribute__((used)) static int
validate_number_field(const char* p_field, size_t i_size)
{
	unsigned char marker = (unsigned char)p_field[0];
	if (marker == 128 || marker == 255 || marker == 0) {
		/* Base-256 marker, there's nothing we can check. */
		return 1;
	} else {
		/* Must be octal */
		size_t i = 0;
		/* Skip any leading spaces */
		while (i < i_size && p_field[i] == ' ') {
			++i;
		}
		/* Skip octal digits. */
		while (i < i_size && p_field[i] >= '0' && p_field[i] <= '7') {
			++i;
		}
		/* Any remaining characters must be space or NUL padding. */
		while (i < i_size) {
			if (p_field[i] != ' ' && p_field[i] != 0) {
				return 0;
			}
			++i;
		}
		return 1;
	}
}