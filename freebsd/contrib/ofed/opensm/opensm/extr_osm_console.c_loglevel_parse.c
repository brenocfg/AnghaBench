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
struct TYPE_3__ {int /*<<< orphan*/  log; } ;
typedef  TYPE_1__ osm_opensm_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,int) ; 
 char* next_token (char**) ; 
 int osm_log_get_level (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  osm_log_set_level (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 
 int strtol (char*,int /*<<< orphan*/ *,int) ; 
 int strtoul (char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void loglevel_parse(char **p_last, osm_opensm_t * p_osm, FILE * out)
{
	char *p_cmd;
	int level;

	p_cmd = next_token(p_last);
	if (!p_cmd)
		fprintf(out, "Current log level is 0x%x\n",
			osm_log_get_level(&p_osm->log));
	else {
		/* Handle x, 0x, and decimal specification of log level */
		if (!strncmp(p_cmd, "x", 1)) {
			p_cmd++;
			level = strtoul(p_cmd, NULL, 16);
		} else {
			if (!strncmp(p_cmd, "0x", 2)) {
				p_cmd += 2;
				level = strtoul(p_cmd, NULL, 16);
			} else
				level = strtol(p_cmd, NULL, 10);
		}
		if ((level >= 0) && (level < 256)) {
			fprintf(out, "Setting log level to 0x%x\n", level);
			osm_log_set_level(&p_osm->log, level);
		} else
			fprintf(out, "Invalid log level 0x%x\n", level);
	}
}