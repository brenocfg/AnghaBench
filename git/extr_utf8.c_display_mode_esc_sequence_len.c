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
 scalar_t__ isdigit (char const) ; 

size_t display_mode_esc_sequence_len(const char *s)
{
	const char *p = s;
	if (*p++ != '\033')
		return 0;
	if (*p++ != '[')
		return 0;
	while (isdigit(*p) || *p == ';')
		p++;
	if (*p++ != 'm')
		return 0;
	return p - s;
}