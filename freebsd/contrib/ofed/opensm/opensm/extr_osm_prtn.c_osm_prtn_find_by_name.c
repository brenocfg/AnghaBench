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
struct TYPE_5__ {int /*<<< orphan*/  prtn_pkey_tbl; } ;
typedef  TYPE_1__ osm_subn_t ;
struct TYPE_6__ {int /*<<< orphan*/  name; int /*<<< orphan*/  map_item; } ;
typedef  TYPE_2__ osm_prtn_t ;
typedef  int /*<<< orphan*/  cl_map_item_t ;

/* Variables and functions */
 int /*<<< orphan*/ * cl_qmap_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cl_qmap_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cl_qmap_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,char const*,int) ; 

osm_prtn_t *osm_prtn_find_by_name(osm_subn_t * p_subn, const char *name)
{
	cl_map_item_t *p_next;
	osm_prtn_t *p;

	p_next = cl_qmap_head(&p_subn->prtn_pkey_tbl);
	while (p_next != cl_qmap_end(&p_subn->prtn_pkey_tbl)) {
		p = (osm_prtn_t *) p_next;
		p_next = cl_qmap_next(&p->map_item);
		if (!strncmp(p->name, name, sizeof(p->name)))
			return p;
	}

	return NULL;
}