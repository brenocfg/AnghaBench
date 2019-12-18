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
 int /*<<< orphan*/  COMMAND_LINE_SIZE ; 
 int __cmdline_find_option_bool (char const*,int /*<<< orphan*/ ,char const*) ; 

int cmdline_find_option_bool(const char *cmdline, const char *option)
{
	return __cmdline_find_option_bool(cmdline, COMMAND_LINE_SIZE, option);
}