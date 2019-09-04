#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  hash; int /*<<< orphan*/  lru; } ;
typedef  TYPE_1__ h2o_filecache_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  h2o_filecache_clear (TYPE_1__*) ; 
 int h2o_linklist_is_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kh_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ kh_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  opencache_set ; 

void h2o_filecache_destroy(h2o_filecache_t *cache)
{
    h2o_filecache_clear(cache);
    assert(kh_size(cache->hash) == 0);
    assert(h2o_linklist_is_empty(&cache->lru));
    kh_destroy(opencache_set, cache->hash);
    free(cache);
}