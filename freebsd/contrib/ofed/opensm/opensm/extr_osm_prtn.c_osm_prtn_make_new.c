#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_11__ {int /*<<< orphan*/  prtn_pkey_tbl; } ;
typedef  TYPE_1__ osm_subn_t ;
struct TYPE_12__ {int /*<<< orphan*/  name; int /*<<< orphan*/  map_item; int /*<<< orphan*/  pkey; } ;
typedef  TYPE_2__ osm_prtn_t ;
typedef  int /*<<< orphan*/  osm_log_t ;

/* Variables and functions */
 int /*<<< orphan*/  OSM_LOG (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char const*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  OSM_LOG_ERROR ; 
 int /*<<< orphan*/  OSM_LOG_VERBOSE ; 
 int /*<<< orphan*/  cl_hton16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_ntoh16 (int /*<<< orphan*/ ) ; 
 scalar_t__ cl_qmap_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  generate_pkey (TYPE_1__*) ; 
 int /*<<< orphan*/  osm_prtn_delete (TYPE_1__*,TYPE_2__**) ; 
 TYPE_2__* osm_prtn_find_by_name (TYPE_1__*,char const*) ; 
 TYPE_2__* osm_prtn_new (char const*,int /*<<< orphan*/ ) ; 

osm_prtn_t *osm_prtn_make_new(osm_log_t * p_log, osm_subn_t * p_subn,
			      const char *name, uint16_t pkey)
{
	osm_prtn_t *p = NULL, *p_check;

	pkey &= cl_hton16((uint16_t) ~ 0x8000);
	if (!pkey) {
		if (name && (p = osm_prtn_find_by_name(p_subn, name)))
			return p;
		if (!(pkey = generate_pkey(p_subn)))
			return NULL;
	}

	p = osm_prtn_new(name, pkey);
	if (!p) {
		OSM_LOG(p_log, OSM_LOG_ERROR, "Unable to create"
			" partition \'%s\' (0x%04x)\n", name, cl_ntoh16(pkey));
		return NULL;
	}

	p_check = (osm_prtn_t *) cl_qmap_insert(&p_subn->prtn_pkey_tbl,
						p->pkey, &p->map_item);
	if (p != p_check) {
		OSM_LOG(p_log, OSM_LOG_VERBOSE, "Duplicated partition"
			" definition: \'%s\' (0x%04x) prev name \'%s\'"
			".  Will use it\n",
			name, cl_ntoh16(pkey), p_check->name);
		osm_prtn_delete(p_subn, &p);
		p = p_check;
	}

	return p;
}