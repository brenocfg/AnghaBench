#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ cmd; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*) ; 
 TYPE_1__* hostapd_cli_commands ; 
 int /*<<< orphan*/  print_cmd_help (int /*<<< orphan*/ *,TYPE_1__*,char*) ; 
 scalar_t__ str_starts (scalar_t__,char const*) ; 

__attribute__((used)) static void print_help(FILE *stream, const char *cmd)
{
	int n;

	fprintf(stream, "commands:\n");
	for (n = 0; hostapd_cli_commands[n].cmd; n++) {
		if (cmd == NULL || str_starts(hostapd_cli_commands[n].cmd, cmd))
			print_cmd_help(stream, &hostapd_cli_commands[n], "  ");
	}
}