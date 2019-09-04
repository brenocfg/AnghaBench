#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ khiter_t ;
struct TYPE_4__ {int /*<<< orphan*/  hash; } ;
typedef  TYPE_1__ h2o_filecache_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ kh_begin (int /*<<< orphan*/ ) ; 
 scalar_t__ kh_end (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kh_exist (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ kh_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_from_cache (TYPE_1__*,scalar_t__) ; 

void h2o_filecache_clear(h2o_filecache_t *cache)
{
    khiter_t iter;
    for (iter = kh_begin(cache->hash); iter != kh_end(cache->hash); ++iter) {
        if (!kh_exist(cache->hash, iter))
            continue;
        release_from_cache(cache, iter);
    }
    assert(kh_size(cache->hash) == 0);
}