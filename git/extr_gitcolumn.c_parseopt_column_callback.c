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
struct option {unsigned int* value; } ;

/* Variables and functions */
 unsigned int COL_ENABLED ; 
 unsigned int COL_ENABLE_MASK ; 
 unsigned int COL_PARSEOPT ; 
 int parse_config (unsigned int*,char const*) ; 

int parseopt_column_callback(const struct option *opt,
			     const char *arg, int unset)
{
	unsigned int *colopts = opt->value;
	*colopts |= COL_PARSEOPT;
	*colopts &= ~COL_ENABLE_MASK;
	if (unset)		/* --no-column == never */
		return 0;
	/* --column == always unless "arg" states otherwise */
	*colopts |= COL_ENABLED;
	if (arg)
		return parse_config(colopts, arg);

	return 0;
}