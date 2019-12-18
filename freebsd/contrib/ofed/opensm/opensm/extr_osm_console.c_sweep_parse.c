#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  sweeping_enabled; } ;
struct TYPE_5__ {TYPE_1__ subn; } ;
typedef  TYPE_2__ osm_opensm_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  help_sweep (int /*<<< orphan*/ *,int) ; 
 char* next_token (char**) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static void sweep_parse(char **p_last, osm_opensm_t * p_osm, FILE * out)
{
	char *p_cmd;

	p_cmd = next_token(p_last);
	if (!p_cmd ||
	    (strcmp(p_cmd, "on") != 0 && strcmp(p_cmd, "off") != 0)) {
		fprintf(out, "Invalid sweep command\n");
		help_sweep(out, 1);
	} else {
		if (strcmp(p_cmd, "on") == 0)
			p_osm->subn.sweeping_enabled = TRUE;
		else
			p_osm->subn.sweeping_enabled = FALSE;
	}
}