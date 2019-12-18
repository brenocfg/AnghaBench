#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  osm_opensm_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* help_function ) (int /*<<< orphan*/ *,int) ;scalar_t__ name; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 TYPE_1__* console_cmds ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  help_command (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* next_token (char**) ; 
 int /*<<< orphan*/  strcmp (char*,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void help_parse(char **p_last, osm_opensm_t * p_osm, FILE * out)
{
	char *p_cmd;
	int i, found = 0;

	p_cmd = next_token(p_last);
	if (!p_cmd)
		help_command(out, 0);
	else {
		for (i = 1; console_cmds[i].name; i++) {
			if (!strcmp(p_cmd, console_cmds[i].name)) {
				found = 1;
				console_cmds[i].help_function(out, 1);
				break;
			}
		}
		if (!found) {
			fprintf(out, "%s : Command not found\n\n", p_cmd);
			help_command(out, 0);
		}
	}
}