#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * out; } ;
struct TYPE_8__ {TYPE_1__ console; } ;
typedef  TYPE_2__ osm_opensm_t ;
struct TYPE_10__ {char* name; int /*<<< orphan*/  (* parse_function ) (char**,TYPE_2__*,int /*<<< orphan*/ *) ;} ;
struct TYPE_9__ {scalar_t__ on; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 TYPE_6__* console_cmds ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  help_command (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ isspace (char) ; 
 TYPE_5__ loop_command ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 char* strtok_r (char*,char*,char**) ; 
 int /*<<< orphan*/  stub1 (char**,TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void parse_cmd_line(char *line, osm_opensm_t * p_osm)
{
	char *p_cmd, *p_last;
	int i, found = 0;
	FILE *out = p_osm->console.out;

	while (isspace(*line))
		line++;
	if (!*line)
		return;

	/* find first token which is the command */
	p_cmd = strtok_r(line, " \t\n\r", &p_last);
	if (p_cmd) {
		for (i = 0; console_cmds[i].name; i++) {
			if (loop_command.on) {
				if (!strcmp(p_cmd, "q")) {
					loop_command.on = 0;
				}
				found = 1;
				break;
			}
			if (!strcmp(p_cmd, console_cmds[i].name)) {
				found = 1;
				console_cmds[i].parse_function(&p_last, p_osm,
							       out);
				break;
			}
		}
		if (!found) {
			fprintf(out, "%s : Command not found\n\n", p_cmd);
			help_command(out, 0);
		}
	} else {
		fprintf(out, "Error parsing command line: `%s'\n", line);
	}
	if (loop_command.on) {
		fprintf(out, "use \"q<ret>\" to quit loop\n");
		fflush(out);
	}
}