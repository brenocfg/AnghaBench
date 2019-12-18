#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {size_t size; TYPE_3__* entries; } ;
typedef  TYPE_2__ h2o_cache_digests_frame_vector_t ;
struct TYPE_5__ {TYPE_3__* entries; } ;
struct TYPE_7__ {TYPE_1__ keys; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_3__*) ; 

__attribute__((used)) static void dispose_frame_vector(h2o_cache_digests_frame_vector_t *v)
{
    size_t i;
    for (i = 0; i != v->size; ++i)
        free(v->entries[i].keys.entries);
    free(v->entries);
}