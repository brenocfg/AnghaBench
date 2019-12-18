#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  osm_ucast_mgr_t ;
typedef  int /*<<< orphan*/  osm_routing_engine_type_t ;
struct TYPE_7__ {int /*<<< orphan*/  p_log; } ;
struct TYPE_8__ {TYPE_1__ ucast_mgr; } ;
struct TYPE_9__ {TYPE_2__ sm; } ;
typedef  TYPE_3__ osm_opensm_t ;
struct TYPE_10__ {int /*<<< orphan*/ * vl_split_count; int /*<<< orphan*/ * srcdest2vl_table; scalar_t__ adj_list_size; int /*<<< orphan*/ * adj_list; int /*<<< orphan*/ * p_mgr; int /*<<< orphan*/  routing_type; } ;
typedef  TYPE_4__ dfsssp_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  OSM_LOG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  OSM_LOG_ERROR ; 
 scalar_t__ malloc (int) ; 

__attribute__((used)) static dfsssp_context_t *dfsssp_context_create(osm_opensm_t * p_osm,
					       osm_routing_engine_type_t
					       routing_type)
{
	dfsssp_context_t *dfsssp_ctx = NULL;

	/* allocate memory */
	dfsssp_ctx = (dfsssp_context_t *) malloc(sizeof(dfsssp_context_t));
	if (dfsssp_ctx) {
		/* set initial values */
		dfsssp_ctx->routing_type = routing_type;
		dfsssp_ctx->p_mgr = (osm_ucast_mgr_t *) & (p_osm->sm.ucast_mgr);
		dfsssp_ctx->adj_list = NULL;
		dfsssp_ctx->adj_list_size = 0;
		dfsssp_ctx->srcdest2vl_table = NULL;
		dfsssp_ctx->vl_split_count = NULL;
	} else {
		OSM_LOG(p_osm->sm.ucast_mgr.p_log, OSM_LOG_ERROR,
			"ERR AD04: cannot allocate memory for dfsssp_ctx in dfsssp_context_create\n");
		return NULL;
	}

	return dfsssp_ctx;
}