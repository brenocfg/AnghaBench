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
 int fst_read_next_text_param (char const*,char*,size_t,char**) ; 

int fst_parse_detach_command(const char *cmd, char *ifname, size_t ifname_size)
{
	char *endp;

	return fst_read_next_text_param(cmd, ifname, ifname_size, &endp);
}