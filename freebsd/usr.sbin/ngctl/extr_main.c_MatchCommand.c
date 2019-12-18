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
struct ngcmd {char const* cmd; char const** aliases; } ;

/* Variables and functions */
 int MAX_CMD_ALIAS ; 
 int /*<<< orphan*/  WHITESPACE ; 
 scalar_t__ strcspn (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (char const*) ; 
 scalar_t__ strncasecmp (char const*,char const*,scalar_t__) ; 

__attribute__((used)) static int
MatchCommand(const struct ngcmd *cmd, const char *s)
{
	int a;

	/* Try to match command, ignoring the usage stuff */
	if (strlen(s) <= strcspn(cmd->cmd, WHITESPACE)) {
		if (strncasecmp(s, cmd->cmd, strlen(s)) == 0)
			return (1);
	}

	/* Try to match aliases */
	for (a = 0; a < MAX_CMD_ALIAS && cmd->aliases[a] != NULL; a++) {
		if (strlen(cmd->aliases[a]) >= strlen(s)) {
			if (strncasecmp(s, cmd->aliases[a], strlen(s)) == 0)
				return (1);
		}
	}

	/* No match */
	return (0);
}