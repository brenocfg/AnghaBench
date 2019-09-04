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
 int match_int_internal (int*,char const*,int,int /*<<< orphan*/ *) ; 

int is_integer(int *out, const char *str, int allow_negative)
{
	return match_int_internal(out, str, allow_negative, NULL);
}