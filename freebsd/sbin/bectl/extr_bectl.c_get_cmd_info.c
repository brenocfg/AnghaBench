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
struct command_map_entry {int /*<<< orphan*/  command; } ;

/* Variables and functions */
 struct command_map_entry* command_map ; 
 size_t nitems (struct command_map_entry*) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct command_map_entry *
get_cmd_info(const char *cmd)
{
	size_t i;

	for (i = 0; i < nitems(command_map); ++i) {
		if (strcmp(cmd, command_map[i].command) == 0)
			return (&command_map[i]);
	}

	return (NULL);
}