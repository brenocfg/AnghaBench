#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* next; struct TYPE_5__* links; } ;
typedef  TYPE_1__ vertex_t ;
typedef  size_t uint32_t ;
typedef  TYPE_1__ link_t ;
struct TYPE_6__ {size_t adj_list_size; TYPE_1__* vl_split_count; int /*<<< orphan*/ * srcdest2vl_table; int /*<<< orphan*/ * adj_list; } ;
typedef  TYPE_3__ dfsssp_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  vltable_dealloc (int /*<<< orphan*/ **) ; 

__attribute__((used)) static void dfsssp_context_destroy(void *context)
{
	dfsssp_context_t *dfsssp_ctx = (dfsssp_context_t *) context;
	vertex_t *adj_list = (vertex_t *) (dfsssp_ctx->adj_list);
	uint32_t i = 0;
	link_t *link = NULL, *tmp = NULL;

	/* free adj_list */
	for (i = 0; i < dfsssp_ctx->adj_list_size; i++) {
		link = adj_list[i].links;
		while (link) {
			tmp = link;
			link = link->next;
			free(tmp);
		}
	}
	free(adj_list);
	dfsssp_ctx->adj_list = NULL;
	dfsssp_ctx->adj_list_size = 0;

	/* free srcdest2vl table and the split count information table
	   (can be done, because dfsssp_context_destroy is called after
	    osm_get_dfsssp_sl)
	 */
	vltable_dealloc(&(dfsssp_ctx->srcdest2vl_table));
	dfsssp_ctx->srcdest2vl_table = NULL;

	if (dfsssp_ctx->vl_split_count) {
		free(dfsssp_ctx->vl_split_count);
		dfsssp_ctx->vl_split_count = NULL;
	}
}