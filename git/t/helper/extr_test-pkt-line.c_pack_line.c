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
 int /*<<< orphan*/  packet_delim (int) ; 
 int /*<<< orphan*/  packet_flush (int) ; 
 int /*<<< orphan*/  packet_write_fmt (int,char*,char const*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static void pack_line(const char *line)
{
	if (!strcmp(line, "0000") || !strcmp(line, "0000\n"))
		packet_flush(1);
	else if (!strcmp(line, "0001") || !strcmp(line, "0001\n"))
		packet_delim(1);
	else
		packet_write_fmt(1, "%s", line);
}