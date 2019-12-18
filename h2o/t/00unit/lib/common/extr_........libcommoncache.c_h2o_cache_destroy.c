#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int flags; int /*<<< orphan*/  mutex; int /*<<< orphan*/  table; } ;
typedef  TYPE_1__ h2o_cache_t ;

/* Variables and functions */
 int H2O_CACHE_FLAG_MULTITHREADED ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  h2o_cache_clear (TYPE_1__*) ; 
 int /*<<< orphan*/  kh_destroy (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 

void h2o_cache_destroy(h2o_cache_t *cache)
{
    h2o_cache_clear(cache);
    kh_destroy(cache, cache->table);
    if ((cache->flags & H2O_CACHE_FLAG_MULTITHREADED) != 0)
        pthread_mutex_destroy(&cache->mutex);
    free(cache);
}