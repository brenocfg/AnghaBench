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
struct pt_regs_offset {int offset; int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 int EINVAL ; 
 struct pt_regs_offset* regoffset_table ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ *,char const*) ; 

int regs_query_register_offset(const char *name)
{
	const struct pt_regs_offset *roff;
	for (roff = regoffset_table; roff->name != NULL; roff++)
		if (!strcmp(roff->name, name))
			return roff->offset;
	return -EINVAL;
}