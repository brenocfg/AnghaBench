#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct osm_routing_engine {int /*<<< orphan*/  destroy; int /*<<< orphan*/  path_sl; int /*<<< orphan*/  ucast_build_fwd_tables; int /*<<< orphan*/ * context; } ;
typedef  int /*<<< orphan*/  osm_opensm_t ;
typedef  int /*<<< orphan*/  lash_t ;

/* Variables and functions */
 int /*<<< orphan*/  get_lash_sl ; 
 int /*<<< orphan*/ * lash_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lash_delete ; 
 int /*<<< orphan*/  lash_process ; 

int osm_ucast_lash_setup(struct osm_routing_engine *r, osm_opensm_t *p_osm)
{
	lash_t *p_lash = lash_create(p_osm);
	if (!p_lash)
		return -1;

	r->context = p_lash;
	r->ucast_build_fwd_tables = lash_process;
	r->path_sl = get_lash_sl;
	r->destroy = lash_delete;

	return 0;
}