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
 int __cmdline_find_option (char const*,int /*<<< orphan*/ ,char const*,char*,int) ; 

int cmdline_find_option(const char *cmdline, const char *option, char *buffer,
			int bufsize)
{
	return __cmdline_find_option(cmdline, COMMAND_LINE_SIZE, option,
				     buffer, bufsize);
}