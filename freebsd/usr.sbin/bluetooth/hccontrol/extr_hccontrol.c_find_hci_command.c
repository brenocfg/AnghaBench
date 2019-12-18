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
struct hci_command {char* command; } ;

/* Variables and functions */
 scalar_t__ strcasecmp (char const*,char*) ; 
 char* strchr (char*,char) ; 
 scalar_t__ strncasecmp (char const*,char*,int) ; 

__attribute__((used)) static struct hci_command *
find_hci_command(char const *command, struct hci_command *category)
{
	struct hci_command	*c = NULL;

	for (c = category; c->command != NULL; c++) {
		char 	*c_end = strchr(c->command, ' ');

		if (c_end != NULL) {
			int	len = c_end - c->command;

			if (strncasecmp(command, c->command, len) == 0)
				return (c);
		} else if (strcasecmp(command, c->command) == 0)
				return (c);
	}

	return (NULL);
}