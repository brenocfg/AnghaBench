#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  h2o_socketpool_target_t ;
struct TYPE_8__ {size_t size; int /*<<< orphan*/ ** entries; } ;
struct TYPE_6__ {int /*<<< orphan*/  sockets; int /*<<< orphan*/  mutex; } ;
struct TYPE_7__ {size_t capacity; int timeout; int /*<<< orphan*/ * balancer; TYPE_4__ targets; TYPE_1__ _shared; } ;
typedef  TYPE_2__ h2o_socketpool_t ;
typedef  int /*<<< orphan*/  h2o_balancer_t ;

/* Variables and functions */
 int /*<<< orphan*/  h2o_linklist_init_anchor (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_vector_reserve (int /*<<< orphan*/ *,TYPE_4__*,size_t) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void common_init(h2o_socketpool_t *pool, h2o_socketpool_target_t **targets, size_t num_targets, size_t capacity,
                        h2o_balancer_t *balancer)
{
    memset(pool, 0, sizeof(*pool));

    pool->capacity = capacity;
    pool->timeout = 2000;

    pthread_mutex_init(&pool->_shared.mutex, NULL);
    h2o_linklist_init_anchor(&pool->_shared.sockets);

    h2o_vector_reserve(NULL, &pool->targets, num_targets);
    for (; pool->targets.size < num_targets; ++pool->targets.size)
        pool->targets.entries[pool->targets.size] = targets[pool->targets.size];

    pool->balancer = balancer;
}