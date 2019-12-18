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
 scalar_t__ strstarts (char const*,char*) ; 

bool module_exit_section(const char *name)
{
	return strstarts(name, ".exit") ||
		strstarts(name, ".ARM.extab.exit") ||
		strstarts(name, ".ARM.exidx.exit");
}