#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_6__ {int sm_priority; } ;
struct TYPE_5__ {TYPE_2__ opt; } ;
struct TYPE_7__ {int /*<<< orphan*/  sm; TYPE_1__ subn; } ;
typedef  TYPE_3__ osm_opensm_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,int) ; 
 char* next_token (char**) ; 
 int /*<<< orphan*/  osm_set_sm_priority (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int strtol (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void priority_parse(char **p_last, osm_opensm_t * p_osm, FILE * out)
{
	char *p_cmd;
	int priority;

	p_cmd = next_token(p_last);
	if (!p_cmd)
		fprintf(out, "Current sm-priority is %d\n",
			p_osm->subn.opt.sm_priority);
	else {
		priority = strtol(p_cmd, NULL, 0);
		if (0 > priority || 15 < priority)
			fprintf(out,
				"Invalid sm-priority %d; must be between 0 and 15\n",
				priority);
		else {
			fprintf(out, "Setting sm-priority to %d\n", priority);
			osm_set_sm_priority(&p_osm->sm, (uint8_t)priority);
		}
	}
}