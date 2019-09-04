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
struct TYPE_5__ {TYPE_2__* str; } ;
struct TYPE_6__ {long n_nodes; struct TYPE_6__* root; TYPE_1__ v; struct TYPE_6__* key; } ;
typedef  TYPE_2__ kson_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_2__*) ; 

void kson_destroy(kson_t *kson)
{
	long i;
	if (kson == 0) return;
	for (i = 0; i < kson->n_nodes; ++i) {
		free(kson->root[i].key); free(kson->root[i].v.str);
	}
	free(kson->root); free(kson);
}