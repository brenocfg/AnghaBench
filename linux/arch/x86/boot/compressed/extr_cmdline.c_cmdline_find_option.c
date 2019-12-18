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
 int __cmdline_find_option (int /*<<< orphan*/ ,char const*,char*,int) ; 
 int /*<<< orphan*/  get_cmd_line_ptr () ; 

int cmdline_find_option(const char *option, char *buffer, int bufsize)
{
	return __cmdline_find_option(get_cmd_line_ptr(), option, buffer, bufsize);
}