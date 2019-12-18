#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_3__* node; } ;
typedef  TYPE_4__ switch_t ;
typedef  int /*<<< orphan*/  osm_log_t ;
struct TYPE_11__ {int num_switches; TYPE_4__** switches; TYPE_1__* p_osm; } ;
typedef  TYPE_5__ lash_t ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_9__ {int dimension; int* coord; int num_links; TYPE_2__** links; } ;
struct TYPE_8__ {size_t switch_id; } ;
struct TYPE_7__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  OSM_LOG (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  OSM_LOG_DEBUG ; 
 int /*<<< orphan*/  OSM_LOG_ENTER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSM_LOG_EXIT (int /*<<< orphan*/ *) ; 
 scalar_t__ snprintf (char*,int,char*,...) ; 
 int sprintf (char*,char*) ; 

__attribute__((used)) static void dump_mesh(lash_t *p_lash)
{
	osm_log_t *p_log = &p_lash->p_osm->log;
	int sw;
	int num_switches = p_lash->num_switches;
	int dimension;
	int i, j, k, n;
	switch_t *s, *s2;
	char buf[256];

	OSM_LOG_ENTER(p_log);

	for (sw = 0; sw < num_switches; sw++) {
		s = p_lash->switches[sw];
		dimension = s->node->dimension;
		n = sprintf(buf, "[");
		for (i = 0; i < dimension; i++) {
			n += snprintf(buf + n, sizeof(buf) - n,
				      "%2d", s->node->coord[i]);
			if (n > sizeof(buf))
				n = sizeof(buf);
			if (i != dimension - 1) {
				n += snprintf(buf + n, sizeof(buf) - n, "%s", ",");
				if (n > sizeof(buf))
					n = sizeof(buf);
			}
		}
		n += snprintf(buf + n, sizeof(buf) - n, "]");
		if (n > sizeof(buf))
			n = sizeof(buf);
		for (j = 0; j < s->node->num_links; j++) {
			s2 = p_lash->switches[s->node->links[j]->switch_id];
			n += snprintf(buf + n, sizeof(buf) - n, " [%d]->[", j);
			if (n > sizeof(buf))
				n = sizeof(buf);
			for (k = 0; k < dimension; k++) {
				n += snprintf(buf + n, sizeof(buf) - n, "%2d",
					      s2->node->coord[k]);
				if (n > sizeof(buf))
					n = sizeof(buf);
				if (k != dimension - 1) {
					n += snprintf(buf + n, sizeof(buf) - n,
						      ",");
					if (n > sizeof(buf))
						n = sizeof(buf);
				}
			}
			n += snprintf(buf + n, sizeof(buf) - n, "]");
			if (n > sizeof(buf))
				n = sizeof(buf);
		}
		OSM_LOG(p_log, OSM_LOG_DEBUG, "%s\n", buf);
	}

	OSM_LOG_EXIT(p_log);
}