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
struct TYPE_2__ {int on; int /*<<< orphan*/  (* loop_function ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int /*<<< orphan*/  previous; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  help_status (int /*<<< orphan*/ *,int) ; 
 TYPE_1__ loop_command ; 
 char* next_token (char**) ; 
 int /*<<< orphan*/  print_status (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void status_parse(char **p_last, osm_opensm_t * p_osm, FILE * out)
{
	char *p_cmd;

	p_cmd = next_token(p_last);
	if (p_cmd) {
		if (strcmp(p_cmd, "loop") == 0) {
			fprintf(out, "Looping on status command...\n");
			fflush(out);
			loop_command.on = 1;
			loop_command.previous = time(NULL);
			loop_command.loop_function = print_status;
		} else {
			help_status(out, 1);
			return;
		}
	}
	print_status(p_osm, out);
}