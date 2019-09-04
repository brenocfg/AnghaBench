#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct round_robin_t {scalar_t__ pos; scalar_t__ consumed_weight; } ;
struct TYPE_3__ {scalar_t__ size; } ;
typedef  TYPE_1__ h2o_socketpool_target_vector_t ;

/* Variables and functions */

__attribute__((used)) static inline void select_next(struct round_robin_t *self, h2o_socketpool_target_vector_t *targets)
{
    self->pos += 1;
    if (self->pos == targets->size)
        self->pos = 0;
    self->consumed_weight = 0;
}