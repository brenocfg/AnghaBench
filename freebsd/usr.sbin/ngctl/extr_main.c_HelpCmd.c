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
struct ngcmd {char const* cmd; char* desc; char** aliases; char* help; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int CMDRTN_OK ; 
 struct ngcmd* FindCommand (char*) ; 
 int MAX_CMD_ALIAS ; 
 struct ngcmd** cmds ; 
 int /*<<< orphan*/  isspace (char const) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int snprintf (char*,int,char*,char const*) ; 
 int strlen (char*) ; 

__attribute__((used)) static int
HelpCmd(int ac, char **av)
{
	const struct ngcmd *cmd;
	int k;

	switch (ac) {
	case 0:
	case 1:
		/* Show all commands */
		printf("Available commands:\n");
		for (k = 0; cmds[k] != NULL; k++) {
			char *s, buf[100];

			cmd = cmds[k];
			snprintf(buf, sizeof(buf), "%s", cmd->cmd);
			for (s = buf; *s != '\0' && !isspace(*s); s++);
			*s = '\0';
			printf("  %-10s %s\n", buf, cmd->desc);
		}
		return (CMDRTN_OK);
	default:
		/* Show help on a specific command */
		if ((cmd = FindCommand(av[1])) != NULL) {
			printf("usage:    %s\n", cmd->cmd);
			if (cmd->aliases[0] != NULL) {
				int a = 0;

				printf("Aliases:  ");
				while (1) {
					printf("%s", cmd->aliases[a++]);
					if (a == MAX_CMD_ALIAS
					    || cmd->aliases[a] == NULL) {
						printf("\n");
						break;
					}
					printf(", ");
				}
			}
			printf("Summary:  %s\n", cmd->desc);
			if (cmd->help != NULL) {
				const char *s;
				char buf[65];
				int tot, len, done;

				printf("Description:\n");
				for (s = cmd->help; *s != '\0'; s += len) {
					while (isspace(*s))
						s++;
					tot = snprintf(buf,
					    sizeof(buf), "%s", s);
					len = strlen(buf);
					done = len == tot;
					if (!done) {
						while (len > 0
						    && !isspace(buf[len-1]))
							buf[--len] = '\0';
					}
					printf("  %s\n", buf);
				}
			}
		}
	}
	return (CMDRTN_OK);
}