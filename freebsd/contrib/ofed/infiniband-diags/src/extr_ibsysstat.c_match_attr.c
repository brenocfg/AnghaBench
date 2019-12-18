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
 int IB_CPUINFO_ATTR ; 
 int IB_HOSTINFO_ATTR ; 
 int IB_PING_ATTR ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static int match_attr(char *str)
{
	if (!strcmp(str, "ping"))
		return IB_PING_ATTR;
	if (!strcmp(str, "host"))
		return IB_HOSTINFO_ATTR;
	if (!strcmp(str, "cpu"))
		return IB_CPUINFO_ATTR;
	return -1;
}