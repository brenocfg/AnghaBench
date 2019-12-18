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
 int dump_qset_params (char const*) ; 

__attribute__((used)) static int
qset_config(int argc, char *argv[], int start_arg, const char *iff_name)
{
	(void) argv;

	if (argc == start_arg)
		return dump_qset_params(iff_name);

	return -1;
}