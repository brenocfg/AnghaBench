#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  osm_log_t ;
struct TYPE_11__ {int balance_limit; scalar_t__ vl_min; TYPE_1__* p_osm; } ;
typedef  TYPE_2__ lash_t ;
struct TYPE_10__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  OSM_LOG_ENTER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSM_LOG_EXIT (int /*<<< orphan*/ *) ; 
 int discover_network_properties (TYPE_2__*) ; 
 int /*<<< orphan*/  free_lash_structures (TYPE_2__*) ; 
 int init_lash_structures (TYPE_2__*) ; 
 int /*<<< orphan*/  lash_cleanup (TYPE_2__*) ; 
 int lash_core (TYPE_2__*) ; 
 int /*<<< orphan*/  populate_fwd_tbls (TYPE_2__*) ; 
 int /*<<< orphan*/  process_switches (TYPE_2__*) ; 

__attribute__((used)) static int lash_process(void *context)
{
	lash_t *p_lash = context;
	osm_log_t *p_log = &p_lash->p_osm->log;
	int status = 0;

	OSM_LOG_ENTER(p_log);

	p_lash->balance_limit = 6;

	/* everything starts here */
	lash_cleanup(p_lash);

	status = discover_network_properties(p_lash);
	if (status)
		goto Exit;

	status = init_lash_structures(p_lash);
	if (status)
		goto Exit;

	process_switches(p_lash);

	status = lash_core(p_lash);
	if (status)
		goto Exit;

	populate_fwd_tbls(p_lash);

Exit:
	if (p_lash->vl_min)
		free_lash_structures(p_lash);
	OSM_LOG_EXIT(p_log);

	return status;
}