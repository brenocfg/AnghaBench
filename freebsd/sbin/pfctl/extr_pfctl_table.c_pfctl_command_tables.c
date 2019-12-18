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
 int pfctl_table (int,char**,char*,char const*,char*,char const*,int) ; 
 int /*<<< orphan*/  usage () ; 

int
pfctl_command_tables(int argc, char *argv[], char *tname,
    const char *command, char *file, const char *anchor, int opts)
{
	if (tname == NULL || command == NULL)
		usage();
	return pfctl_table(argc, argv, tname, command, file, anchor, opts);
}