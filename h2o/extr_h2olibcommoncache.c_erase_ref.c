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
typedef  int /*<<< orphan*/  khiter_t ;
struct TYPE_10__ {int /*<<< orphan*/  size; int /*<<< orphan*/  table; } ;
typedef  TYPE_2__ h2o_cache_t ;
struct TYPE_9__ {scalar_t__ len; } ;
struct TYPE_11__ {TYPE_1__ value; int /*<<< orphan*/  _age_link; int /*<<< orphan*/  _lru_link; } ;
typedef  TYPE_3__ h2o_cache_ref_t ;

/* Variables and functions */
 int /*<<< orphan*/  h2o_cache_release (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  h2o_linklist_unlink (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kh_del (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* kh_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void erase_ref(h2o_cache_t *cache, khiter_t iter, int reuse)
{
    h2o_cache_ref_t *ref = kh_key(cache->table, iter);

    if (!reuse)
        kh_del(cache, cache->table, iter);
    h2o_linklist_unlink(&ref->_lru_link);
    h2o_linklist_unlink(&ref->_age_link);
    cache->size -= ref->value.len;

    h2o_cache_release(cache, ref);
}