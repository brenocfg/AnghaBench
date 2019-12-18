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
 scalar_t__ git_parse_int (char const*,int*) ; 
 int git_parse_maybe_bool_text (char const*) ; 

int git_parse_maybe_bool(const char *value)
{
	int v = git_parse_maybe_bool_text(value);
	if (0 <= v)
		return v;
	if (git_parse_int(value, &v))
		return !!v;
	return -1;
}