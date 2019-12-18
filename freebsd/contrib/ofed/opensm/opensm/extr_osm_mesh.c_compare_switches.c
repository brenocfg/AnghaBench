#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_3__* node; } ;
typedef  TYPE_4__ switch_t ;
struct TYPE_11__ {TYPE_2__* mesh; TYPE_1__* p_lash; } ;
typedef  TYPE_5__ sort_ctx_t ;
struct TYPE_12__ {size_t index; TYPE_5__ ctx; } ;
typedef  TYPE_6__ comp_t ;
struct TYPE_9__ {int* coord; } ;
struct TYPE_8__ {int dimension; int* dim_order; } ;
struct TYPE_7__ {TYPE_4__** switches; } ;

/* Variables and functions */

__attribute__((used)) static int compare_switches(const void *p1, const void *p2)
{
	const comp_t *cp1 = p1, *cp2 = p2;
	const sort_ctx_t *ctx = &cp1->ctx;
	switch_t *s1 = ctx->p_lash->switches[cp1->index];
	switch_t *s2 = ctx->p_lash->switches[cp2->index];
	int i, j;
	int ret;

	for (i = 0; i < ctx->mesh->dimension; i++) {
		j = ctx->mesh->dim_order[i];
		ret = s1->node->coord[j] - s2->node->coord[j];
		if (ret)
			return ret;
	}

	return 0;
}