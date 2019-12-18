#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {size_t size; TYPE_3__** entries; } ;
typedef  TYPE_4__ h2o_socketpool_target_vector_t ;
struct TYPE_7__ {scalar_t__ weight_m1; } ;
struct TYPE_6__ {unsigned int leased_count; } ;
struct TYPE_8__ {TYPE_2__ conf; TYPE_1__ _shared; } ;

/* Variables and functions */

__attribute__((used)) static int check_weight_distribution(h2o_socketpool_target_vector_t *targets)
{
    size_t i, j;

    for (i = 0; i < targets->size; i++) {
        for (j = i + 1; j < targets->size; j++) {
            if (targets->entries[i]->_shared.leased_count * ((unsigned)targets->entries[j]->conf.weight_m1 + 1) !=
                targets->entries[j]->_shared.leased_count * ((unsigned)targets->entries[i]->conf.weight_m1 + 1))
                return 0;
        }
    }
    return 1;
}