#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  force_heavy_sweep; } ;
struct TYPE_6__ {TYPE_1__ subn; } ;
typedef  TYPE_2__ osm_opensm_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  help_resweep (int /*<<< orphan*/ *,int) ; 
 char* next_token (char**) ; 
 int /*<<< orphan*/  osm_opensm_sweep (TYPE_2__*) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static void resweep_parse(char **p_last, osm_opensm_t * p_osm, FILE * out)
{
	char *p_cmd;

	p_cmd = next_token(p_last);
	if (!p_cmd ||
	    (strcmp(p_cmd, "heavy") != 0 && strcmp(p_cmd, "light") != 0)) {
		fprintf(out, "Invalid resweep command\n");
		help_resweep(out, 1);
	} else {
		if (strcmp(p_cmd, "heavy") == 0)
			p_osm->subn.force_heavy_sweep = TRUE;
		osm_opensm_sweep(p_osm);
	}
}