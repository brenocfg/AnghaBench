#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_10__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ h2o_iovec_t ;
typedef  int /*<<< orphan*/  h2o_cache_t ;
struct TYPE_9__ {int /*<<< orphan*/  len; int /*<<< orphan*/  base; } ;
struct TYPE_11__ {TYPE_1__ value; } ;
typedef  TYPE_3__ h2o_cache_ref_t ;

/* Variables and functions */
 int /*<<< orphan*/  H2O_CACHE_FLAG_EARLY_UPDATE ; 
 int /*<<< orphan*/  H2O_STRLIT (char*) ; 
 int bytes_destroyed ; 
 int /*<<< orphan*/ * h2o_cache_create (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_cache_delete (int /*<<< orphan*/ *,int,TYPE_2__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_cache_destroy (int /*<<< orphan*/ *) ; 
 TYPE_3__* h2o_cache_fetch (int /*<<< orphan*/ *,int,TYPE_2__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_cache_release (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  h2o_cache_set (int /*<<< orphan*/ *,int,TYPE_2__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_iovec_init (int /*<<< orphan*/ ) ; 
 int h2o_memis (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int) ; 
 int /*<<< orphan*/  on_destroy ; 

void test_lib__common__cache_c(void)
{
    h2o_cache_t *cache = h2o_cache_create(H2O_CACHE_FLAG_EARLY_UPDATE, 1024, 1000, on_destroy);
    uint64_t now = 0;
    h2o_iovec_t key = {H2O_STRLIT("key")};
    h2o_cache_ref_t *ref;

    /* fetch "key" */
    ref = h2o_cache_fetch(cache, now, key, 0);
    ok(ref == NULL);

    /* set "key" => "value" */
    h2o_cache_set(cache, now, key, 0, h2o_iovec_init(H2O_STRLIT("value")));

    /* delete "key" */
    h2o_cache_delete(cache, now, key, 0);
    ref = h2o_cache_fetch(cache, now, key, 0);
    ok(ref == NULL);

    /* set "key" => "value" */
    h2o_cache_set(cache, now, key, 0, h2o_iovec_init(H2O_STRLIT("value")));

    /* fetch "key" */
    ref = h2o_cache_fetch(cache, now, key, 0);
    ok(h2o_memis(ref->value.base, ref->value.len, H2O_STRLIT("value")));
    h2o_cache_release(cache, ref);

    /* proceed 999ms */
    now += 999;

    /* should fail to fetch "key" */
    ref = h2o_cache_fetch(cache, now, key, 0);
    ok(ref == NULL);

    /* refetch should succeed */
    ref = h2o_cache_fetch(cache, now, key, 0);
    ok(h2o_memis(ref->value.base, ref->value.len, H2O_STRLIT("value")));
    h2o_cache_release(cache, ref);

    /* set "key" to "value2" */
    h2o_cache_set(cache, now, key, 0, h2o_iovec_init(H2O_STRLIT("value2")));

    /* fetch */
    ref = h2o_cache_fetch(cache, now, key, 0);
    ok(h2o_memis(ref->value.base, ref->value.len, H2O_STRLIT("value2")));
    h2o_cache_release(cache, ref);

    ok(bytes_destroyed == 10);

    h2o_cache_destroy(cache);

    ok(bytes_destroyed == 16);
}