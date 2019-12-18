#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {size_t size; TYPE_4__** entries; int /*<<< orphan*/ * member_0; } ;
typedef  TYPE_3__ h2o_socketpool_target_vector_t ;
struct TYPE_9__ {scalar_t__ weight_m1; } ;
struct TYPE_8__ {scalar_t__ leased_count; } ;
struct TYPE_11__ {TYPE_2__ conf; TYPE_1__ _shared; } ;
typedef  TYPE_4__ h2o_socketpool_target_t ;

/* Variables and functions */
 TYPE_4__* h2o_mem_alloc (int) ; 
 int /*<<< orphan*/  h2o_vector_reserve (int /*<<< orphan*/ *,TYPE_3__*,size_t) ; 

__attribute__((used)) static h2o_socketpool_target_vector_t gen_targets(size_t size)
{
    size_t i;
    h2o_socketpool_target_vector_t targets = {NULL};

    h2o_vector_reserve(NULL, &targets, size);
    for (i = 0; i < size; i++) {
        h2o_socketpool_target_t *target = h2o_mem_alloc(sizeof(*target));
        target->_shared.leased_count = 0;
        target->conf.weight_m1 = 0;
        targets.entries[i] = target;
    }
    targets.size = size;

    return targets;
}