#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct round_robin_t {size_t pos; scalar_t__ consumed_weight; int /*<<< orphan*/  mutex; } ;
struct TYPE_8__ {size_t size; TYPE_2__** entries; } ;
typedef  TYPE_3__ h2o_socketpool_target_vector_t ;
typedef  int /*<<< orphan*/  h2o_balancer_t ;
struct TYPE_6__ {scalar_t__ weight_m1; } ;
struct TYPE_7__ {TYPE_1__ conf; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  h2o_fatal (char*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  select_next (struct round_robin_t*,TYPE_3__*) ; 

__attribute__((used)) static size_t selector(h2o_balancer_t *balancer, h2o_socketpool_target_vector_t *targets, char *tried)
{
    size_t i;
    size_t result = 0;
    struct round_robin_t *self = (void *)balancer;

    pthread_mutex_lock(&self->mutex);

    assert(targets->size != 0);
    for (i = 0; i < targets->size; i++) {
        if (!tried[self->pos]) {
            /* get the result */
            result = self->pos;
            if (++self->consumed_weight > targets->entries[self->pos]->conf.weight_m1)
                select_next(self, targets);
            pthread_mutex_unlock(&self->mutex);
            return result;
        } else {
            select_next(self, targets);
        }
    }
    h2o_fatal("unreachable");
}