#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_7__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_8__ {int /*<<< orphan*/  map_item; } ;
typedef  TYPE_1__ osm_switch_t ;
struct TYPE_10__ {int /*<<< orphan*/  sw_guid_tbl; } ;
struct TYPE_9__ {int /*<<< orphan*/  lock; TYPE_7__ subn; } ;
typedef  TYPE_2__ osm_opensm_t ;
typedef  int /*<<< orphan*/  cl_qmap_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  cl_hton64 (scalar_t__) ; 
 int /*<<< orphan*/  cl_plock_acquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_plock_release (int /*<<< orphan*/ *) ; 
 scalar_t__ cl_qmap_end (int /*<<< orphan*/ *) ; 
 scalar_t__ cl_qmap_head (int /*<<< orphan*/ *) ; 
 scalar_t__ cl_qmap_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  help_switchbalance (int /*<<< orphan*/ *,int) ; 
 char* next_token (char**) ; 
 TYPE_1__* osm_get_switch_by_guid (TYPE_7__*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,char*) ; 
 scalar_t__ strtoull (char*,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  switchbalance_check (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void switchbalance_parse(char **p_last, osm_opensm_t * p_osm, FILE * out)
{
	char *p_cmd;
	uint64_t guid = 0;
	osm_switch_t *p_sw;
	int verbose = 0;

	p_cmd = next_token(p_last);
	if (p_cmd) {
		char *p_end;

		if (strcmp(p_cmd, "verbose") == 0) {
			verbose++;
			p_cmd = next_token(p_last);
		}

		if (p_cmd) {
			guid = strtoull(p_cmd, &p_end, 0);
			if (!guid || *p_end != '\0') {
				fprintf(out, "Invalid guid specified\n");
				help_switchbalance(out, 1);
				return;
			}
		}
	}

	cl_plock_acquire(&p_osm->lock);
	if (guid) {
		p_sw = osm_get_switch_by_guid(&p_osm->subn, cl_hton64(guid));
		if (!p_sw) {
			fprintf(out, "guid not found\n");
			goto lock_exit;
		}

		switchbalance_check(p_osm, p_sw, out, verbose);
	} else {
		cl_qmap_t *p_sw_guid_tbl = &p_osm->subn.sw_guid_tbl;
		for (p_sw = (osm_switch_t *) cl_qmap_head(p_sw_guid_tbl);
		     p_sw != (osm_switch_t *) cl_qmap_end(p_sw_guid_tbl);
		     p_sw = (osm_switch_t *) cl_qmap_next(&p_sw->map_item))
			switchbalance_check(p_osm, p_sw, out, verbose);
	}
lock_exit:
	cl_plock_release(&p_osm->lock);
	return;
}