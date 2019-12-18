#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  khiter_t ;
struct TYPE_12__ {int /*<<< orphan*/  len; int /*<<< orphan*/  base; } ;
typedef  TYPE_1__ h2o_iovec_t ;
struct TYPE_13__ {int /*<<< orphan*/  table; } ;
typedef  TYPE_2__ h2o_cache_t ;
struct TYPE_14__ {scalar_t__ keyhash; TYPE_1__ key; } ;
typedef  TYPE_3__ h2o_cache_ref_t ;
typedef  scalar_t__ h2o_cache_hashcode_t ;

/* Variables and functions */
 int /*<<< orphan*/  erase_ref (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ h2o_cache_calchash (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kh_end (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kh_get (TYPE_2__*,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  lock_cache (TYPE_2__*) ; 
 int /*<<< orphan*/  purge (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_cache (TYPE_2__*) ; 

void h2o_cache_delete(h2o_cache_t *cache, uint64_t now, h2o_iovec_t key, h2o_cache_hashcode_t keyhash)
{
    h2o_cache_ref_t search_key;
    khiter_t iter;

    if (keyhash == 0)
        keyhash = h2o_cache_calchash(key.base, key.len);
    search_key.key = key;
    search_key.keyhash = keyhash;

    lock_cache(cache);

    purge(cache, now);

    if ((iter = kh_get(cache, cache->table, &search_key)) != kh_end(cache->table))
        erase_ref(cache, iter, 0);

    unlock_cache(cache);
}