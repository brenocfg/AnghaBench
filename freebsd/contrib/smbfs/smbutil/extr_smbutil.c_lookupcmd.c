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
struct commands {scalar_t__ name; } ;

/* Variables and functions */
 struct commands* commands ; 
 scalar_t__ strcmp (scalar_t__,char const*) ; 

__attribute__((used)) static struct commands *
lookupcmd(const char *name)
{
	struct commands *cmd;

	for (cmd = commands; cmd->name; cmd++) {
		if (strcmp(cmd->name, name) == 0)
			return cmd;
	}
	return NULL;
}