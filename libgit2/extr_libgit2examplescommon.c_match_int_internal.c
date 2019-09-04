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
 int /*<<< orphan*/  fatal (char*,char const*) ; 
 scalar_t__ strtol (char const*,char**,int) ; 

__attribute__((used)) static int match_int_internal(
	int *out, const char *str, int allow_negative, const char *opt)
{
	char *endptr = NULL;
	int	  val = (int)strtol(str, &endptr, 10);

	if (!endptr || *endptr != '\0')
		fatal("expected number", opt);
	else if (val < 0 && !allow_negative)
		fatal("negative values are not allowed", opt);

	if (out)
		*out = val;

	return 1;
}