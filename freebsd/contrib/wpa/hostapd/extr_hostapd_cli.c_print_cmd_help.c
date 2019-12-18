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
struct hostapd_cli_cmd {char* usage; int /*<<< orphan*/  cmd; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 

__attribute__((used)) static void print_cmd_help(FILE *stream, const struct hostapd_cli_cmd *cmd,
			   const char *pad)
{
	char c;
	size_t n;

	if (cmd->usage == NULL)
		return;
	fprintf(stream, "%s%s ", pad, cmd->cmd);
	for (n = 0; (c = cmd->usage[n]); n++) {
		fprintf(stream, "%c", c);
		if (c == '\n')
			fprintf(stream, "%s", pad);
	}
	fprintf(stream, "\n");
}