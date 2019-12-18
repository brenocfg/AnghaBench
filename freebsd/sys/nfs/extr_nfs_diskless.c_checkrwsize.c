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
 int /*<<< orphan*/  printf (char*,char const*,unsigned long) ; 

__attribute__((used)) static int
checkrwsize(unsigned long v, const char *name)
{
	/*
	 * 32K is used as an upper bound because most servers
	 * limit block size to satisfy IPv4's limit of
	 * 64K/reassembled packet.  The lower bound is pretty
	 * much arbitrary.
	 */
	if (!(4 <= v && v <= 32*1024)) {
		printf("nfs_parse_options: invalid %s %lu ignored\n", name, v);
		return 0;
	} else
		return 1;
}